#include <sstream>
#include <iostream>

#include "../states/game_state.h"
#include "../states/credits_state.h"

CreditsState::CreditsState(GameData data): datagame(data){
    
}

void CreditsState::Init(){
    motor = Motor2D::Instance();    

    motor->view.zoom(0.9);
    motor->view.setCenter(SCREEN_WIDTH/2 , SCREEN_HEIGHT/2);
    motor->window.setView(motor->view);



    std::string titulos[Max_credits] = {"Desarrolladores", "Angel Torregrosa Calabuig" , "Laura Garcia Hernandez","Alba Ruiz Maiques", "Antonio David Ortiz Peral", "Alfredo Perez Pinedo", "Pulsa Esc para ir atras"};


    for (int i = 0; i < Max_credits; i++)
    {
        creditsTitle[i].setFont(motor->getFont("Main Font"));
        
        creditsTitle[i].setColor(sf::Color::White);

        creditsTitle[i].setString(titulos[i]);

        if (i==0)
        {
            creditsTitle[i].setCharacterSize(60);
        }else{
            creditsTitle[i].setCharacterSize(25);
        }
        
        creditsTitle[i].setOrigin(creditsTitle[i].getLocalBounds().width/2, 
        creditsTitle[i].getLocalBounds().height/2);
        creditsTitle[i].setPosition(sf::Vector2f(SCREEN_WIDTH/2 , SCREEN_HEIGHT/(Max_credits+1)*(i+1)));
    }
}

void CreditsState::HandleInput()
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

                    case sf::Keyboard::Escape:

                        datagame->states.popState();
                        
                        break;

                    default:
                        break;
                }
            }
        }
    }

void CreditsState::Update(const float &dt){
   
}

void CreditsState::Render(const float &dt){
    
    motor->window.clear();

    for (int i = 0; i < Max_credits; i++)
    {
        motor->drawText(this->creditsTitle[i]);
    }

    motor->window.display();
}
