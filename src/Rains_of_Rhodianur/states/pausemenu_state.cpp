#include <sstream>
#include <iostream>

#include "../states/pausemenu_state.h"
#include "../states/options_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"

PauseMenuState::PauseMenuState(GameData data): datagame(data){
    
}

void PauseMenuState::Init(){
    motor = Motor2D::Instance();
    motor->addFont("Main Font3", MAIN_FONT);
    
    GameState *estadoJuego = GameState::Instance();
    estadoJuego->music.pause();


    std::string titulos[Max_pause_menu] = {"Menu de pausa", "Reanudar", "Opciones", "Salir al menu principal"};



    for (int i = 0; i < Max_pause_menu; i++)
    {
        menuPause[i].setFont(motor->getFont("Main Font3"));
        if (i==1)
        {
            menuPause[i].setColor(sf::Color::Red);
        }else{
            menuPause[i].setColor(sf::Color::White);
        }

        menuPause[i].setString(titulos[i]);

        if (i==0)
        {
            menuPause[i].setCharacterSize(60);
        }else{
            menuPause[i].setCharacterSize(25);
        }
        
        menuPause[i].setOrigin(menuPause[i].getLocalBounds().width/2, 
                                menuPause[i].getLocalBounds().height/2);
    }


    menuPause[0].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 150.f)));
    menuPause[1].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 50.f)));
    menuPause[2].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y +50)));
    menuPause[3].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y + 150.f)));

    menuPauseSelected = 1;
}

void PauseMenuState::HandleInput()
    {
        sf::Event event;
        GameState *estadoJuego = GameState::Instance();
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

                        switch (menuPausePressed())
                        {
                            case 1:
                            
                                if(estadoJuego->musicaActiva){
                                    estadoJuego->music.play();
                                }

                                //Go to Game Screen
                                datagame->states.popState();

                                break;

                            case 2:
                                //Go to Options Screen
                                datagame->states.addState(state_ptr(new OptionsState(this->datagame)));
                                break;

                            case 3:
                                //Go to Main Menu
                                delete estadoJuego->zonactual;
                                delete estadoJuego->jugador;
                                datagame->states.addState(state_ptr(new MainMenuState(this->datagame)));
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

void PauseMenuState::Update(const float &dt){
   
}

void PauseMenuState::Render(const float &dt){

    motor->window.clear();

    for (int i = 0; i < Max_pause_menu; i++)
    {
        motor->drawText(this->menuPause[i]);
    }

    motor->window.display();
}

void PauseMenuState:: moveDown(){
    if(menuPauseSelected + 1 <= Max_pause_menu){
        menuPause[menuPauseSelected].setColor(sf::Color::White);

        menuPauseSelected++;
        if (menuPauseSelected == 4)
        {
            menuPauseSelected = 1;
        }
            
        menuPause[menuPauseSelected].setColor(sf::Color::Red);
    }
}

void PauseMenuState:: moveUp(){
    if(menuPauseSelected - 1 >= 0){
        menuPause[menuPauseSelected].setColor(sf::Color::White);

        menuPauseSelected--;
        if (menuPauseSelected == 0)
        {
            menuPauseSelected = 3;
        }
            
        menuPause[menuPauseSelected].setColor(sf::Color::Red);
    }
}

int PauseMenuState:: menuPausePressed(){
    return menuPauseSelected;
}
