#include <sstream>
#include <iostream>

#include "../states/game_state.h"
#include "../states/control_state.h"
#include "../states/credits_state.h"

MainMenuState::MainMenuState(GameData data): datagame(data){
    
}

void MainMenuState::Init(){
    motor = Motor2D::Instance();    

    motor->view.zoom(0.9);
    motor->view.setCenter(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2);
    motor->window.setView(motor->view);



    std::string titulos[Max_main_menu] = {"Rains of Rhodianur", "Jugar", "Boss Rush","Controles", "Creditos", "Salir"};


    for (int i = 0; i < Max_main_menu; i++)
    {
        mainMenu[i].setFont(motor->getFont("Main Font"));
        if (i==1)
        {
            mainMenu[i].setColor(sf::Color::Red);
        }else{
            mainMenu[i].setColor(sf::Color::White);
        }

        mainMenu[i].setString(titulos[i]);

        if (i==0)
        {
            mainMenu[i].setCharacterSize(60);
        }else{
            mainMenu[i].setCharacterSize(25);
        }
        
        mainMenu[i].setOrigin(mainMenu[i].getLocalBounds().width/2, 
        mainMenu[i].getLocalBounds().height/2);
        mainMenu[i].setPosition(sf::Vector2f(SCREEN_WIDTH/2 , SCREEN_HEIGHT/(Max_main_menu+1)*(i+1)));
    }

    mainMenuSelected = 1;
}

void MainMenuState::HandleInput()
    {
        sf::Event event;
        

        while (motor->window.pollEvent(event))
        {
        
            switch (event.type) {

            //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    motor->window.close();
                    break;

                case sf::Event::JoystickButtonPressed:

                    if(sf::Joystick::isButtonPressed(0,0) && mainMenuPressed()==1){
                        datagame->states.addState(state_ptr(GameState::Instance(this->datagame)));
                    }

                    break;


                case sf::Event::JoystickMoved:

                        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)==100 ){ moveDown();}

                        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)==-100 ){ moveUp();}

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

                        switch (mainMenuPressed())
                        {
                            case 1:
                                
                                datagame->states.addState(state_ptr(GameState::Instance(this->datagame)));
                                break;

                            case 2:
                                //Go to Boss Rush Screen
                                break;

                            case 3:
                                datagame->states.addState(state_ptr(new ControlState(this->datagame, 1)),false);
                                break;

                            case 4:
                                datagame->states.addState(state_ptr(new CreditsState(this->datagame)),false);
                                break;

                            case 5:
                                motor->window.close();
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

void MainMenuState::Update(const float &dt){
   
}

void MainMenuState::Render(const float &dt){
    
    motor->window.clear();

    for (int i = 0; i < Max_main_menu; i++)
    {
        motor->drawText(this->mainMenu[i]);
    }

    motor->window.display();
}

void MainMenuState:: moveDown(){
    if(mainMenuSelected + 1 <= Max_main_menu){
        mainMenu[mainMenuSelected].setColor(sf::Color::White);

        mainMenuSelected++;
        if (mainMenuSelected == 6)
        {
            mainMenuSelected = 1;
        }
            
        mainMenu[mainMenuSelected].setColor(sf::Color::Red);
    }
}

void MainMenuState:: moveUp(){
    if(mainMenuSelected - 1 >= 0){
        mainMenu[mainMenuSelected].setColor(sf::Color::White);

        mainMenuSelected--;
        if (mainMenuSelected == 0)
        {
            mainMenuSelected = 5;
        }
            
        mainMenu[mainMenuSelected].setColor(sf::Color::Red);
    }
}

int MainMenuState:: mainMenuPressed(){
    return mainMenuSelected;
}
