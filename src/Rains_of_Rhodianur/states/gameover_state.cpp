#include <sstream>
#include <iostream>

#include "../states/gameover_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"

GameOverState::GameOverState(GameData data): datagame(data){
    
}

void GameOverState::Init(){
    motor = Motor2D::Instance();
    //motor->addFont("Main Font2", MAIN_FONT);
    
    GameState *estadoJuego = GameState::Instance();
    estadoJuego->music.stop();  


    std::string titulos[Max_gameover_menu] = {"Game Over", "Reanudar desde checkpoint", "Salir al menu principal"};


    for (int i = 0; i < Max_gameover_menu; i++)
    {
        menuGameOver[i].setFont(motor->getFont("Main Font"));
        if (i==1)
        {
            menuGameOver[i].setColor(sf::Color::Red);
        }else{
            menuGameOver[i].setColor(sf::Color::White);
        }

        menuGameOver[i].setString(titulos[i]);

        if (i==0)
        {
            menuGameOver[i].setCharacterSize(60);
        }else{
            menuGameOver[i].setCharacterSize(25);
        }
        
        menuGameOver[i].setOrigin(menuGameOver[i].getLocalBounds().width/2, 
                                menuGameOver[i].getLocalBounds().height/2);
       
    }
    menuGameOver[0].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 150.f)));
    menuGameOver[1].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y - 50.f)));
    menuGameOver[2].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y +50)));
    menuGameOver[3].setPosition(sf::Vector2f(motor->view.getCenter().x, (motor->view.getCenter().y + 150.f)));

    menuGameOverSelected = 1;
}

void GameOverState::HandleInput()
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

                        switch (menuGameOverPressed())
                        {
                            case 1:
                            
                                if(estadoJuego->musicaActiva){
                                    estadoJuego->music.play();
                                }
                                //Go to Game Screen
                                
                                estadoJuego->reaparecerCheckpoint();

                                break;

                            case 2:

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

void GameOverState::Update(const float &dt){
   
}

void GameOverState::Render(const float &dt){

    motor->window.clear();
    
    for (int i = 0; i < Max_gameover_menu; i++)
    {
        motor->drawText(this->menuGameOver[i]);
    }

    motor->window.display();
}

void GameOverState:: moveDown(){
    if(menuGameOverSelected + 1 <= Max_gameover_menu){
        menuGameOver[menuGameOverSelected].setColor(sf::Color::White);

        menuGameOverSelected++;
        if (menuGameOverSelected == 3)
        {
            menuGameOverSelected = 1;
        }
            
        menuGameOver[menuGameOverSelected].setColor(sf::Color::Red);
    }
}

void GameOverState:: moveUp(){
    if(menuGameOverSelected - 1 >= 0){
        menuGameOver[menuGameOverSelected].setColor(sf::Color::White);

        menuGameOverSelected--;
        if (menuGameOverSelected == 0)
        {
            menuGameOverSelected = 2;
        }
            
        menuGameOver[menuGameOverSelected].setColor(sf::Color::Red);
    }
}

int GameOverState:: menuGameOverPressed(){
    return menuGameOverSelected;
}
