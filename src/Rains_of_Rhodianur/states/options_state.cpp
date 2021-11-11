#include <sstream>
#include <iostream>

#include "../states/options_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"
#include "../states/control_state.h"

OptionsState::OptionsState(GameData data): datagame(data){
    motor = Motor2D::Instance(); 
}

void OptionsState::Init(){
   motor = Motor2D::Instance();
    //motor->addFont("Main Font", MAIN_FONT);
    
    GameState *estadoJuego = GameState::Instance();
    estadoJuego->music.pause();

    std::string titulosOpciones[Max_options_menu] = {"Opciones", "Controles", "Configuracion del sonido", "Sonido activado", "Atras"};
    
    if(!estadoJuego->musicaActiva){
       titulosOpciones[3] = "Sonido desactivado";
    }
    



    for (int i = 0; i < Max_options_menu; i++)
    {
        optionsMenu[i].setFont(motor->getFont("Main Font"));
        if (i==1)
        {
            optionsMenu[i].setColor(sf::Color::Red);
        }else{
            optionsMenu[i].setColor(sf::Color::Yellow);
        }

        optionsMenu[i].setString(titulosOpciones[i]);

        if (i==0)
        {
            optionsMenu[i].setCharacterSize(60);
        }else{
            optionsMenu[i].setCharacterSize(25);
        }
        
        optionsMenu[i].setOrigin(optionsMenu[i].getLocalBounds().width/2, 
                                optionsMenu[i].getLocalBounds().height/2);
    }


    optionsMenu[0].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 150.f)));
    optionsMenu[1].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 50.f)));
    optionsMenu[2].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y +50)));
    optionsMenu[3].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y + 150.f)));
    optionsMenu[4].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y + 250.f)));

    optionSelected = 1;
}

void OptionsState::HandleInput()
    {
        sf::Event event;
        while (motor->window.pollEvent(event))
        {
        
            switch (event.type) {

            //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    motor->window.close();
                    break;

                case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                    case sf::Keyboard::Up:
                        moveUp();
                        break;

                    case sf::Keyboard::Down:
                        moveDown();
                        break;

                    case sf::Keyboard::Return:

                        switch (optionsPressed())
                        {

                            case 1:
                                datagame->states.addState(state_ptr(new ControlState(this->datagame,2)));
                                break;
                            
                            case 4:
                                //Go to Pausa
                                datagame->states.addState(state_ptr(new PauseMenuState(this->datagame)));
                                break;

                            case 3:
                                //Desactivar sonido
                                modificarSonido();
                                break;
                            
                            default:
                                break;
                        }
                    
                    default:
                        break;
                }
            }
        }
    }

void OptionsState::Update(const float &dt){
   
}

void OptionsState::Render(const float &dt){

    motor->window.clear();

    for (int i = 0; i < Max_options_menu; i++)
    {
        motor->drawText(this->optionsMenu[i]);
    }

    motor->window.display();
}

void OptionsState:: moveDown(){
    if(optionSelected + 1 <= Max_options_menu){
        optionsMenu[optionSelected].setColor(sf::Color::Yellow);

        optionSelected++;
        if (optionSelected == 5)
        {
            optionSelected = 1;
        }else if (optionSelected == 2)
        {
            optionSelected = 3;
        }
        
            
        optionsMenu[optionSelected].setColor(sf::Color::Red);
    }
}

void OptionsState:: moveUp(){
    if(optionSelected - 1 >= 0){
        optionsMenu[optionSelected].setColor(sf::Color::Yellow);

        optionSelected--;
        if (optionSelected == 2)
        {
            optionSelected = 1;
        }else if (optionSelected == 0)
        {
            optionSelected = 4;
        }
            
        optionsMenu[optionSelected].setColor(sf::Color::Red);
    }
}

int OptionsState:: optionsPressed(){
    return optionSelected;
}

void OptionsState::modificarSonido(){
    if(optionSelected == 3){
        //pausar la variable global de música o activarla
        GameState *estadoJuego = GameState::Instance();
        
        if(estadoJuego->musicaActiva){
            optionsMenu[optionSelected].setString("Sonido desactivado");
            estadoJuego->musicaActiva = false;
        }else{
            optionsMenu[optionSelected].setString("Sonido activado");
            estadoJuego->musicaActiva = true;
        }
    }
    float dt=0.0;
    Render(dt);
}