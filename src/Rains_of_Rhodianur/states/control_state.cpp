#include <sstream>
#include <iostream>

#include "../states/control_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"
#include "../states/options_state.h"

ControlState::ControlState(GameData data, int id): datagame(data){
    idFrom = id;
}

void ControlState::Init(){
    motor = Motor2D::Instance();
    motor->addTexture("Controles", CONTROLES_FILEPATH);
    sprite.setTexture(motor->getTexture("Controles"));
    sprite.setOrigin(0,0);
    if(idFrom == 2){
        sprite.setPosition(motor->view.getCenter().x - 355.f, motor->view.getCenter().y - 300.f);
        sprite.scale(0.55f,0.85f);
    }else if(idFrom == 1){
        sprite.setPosition(motor->view.getCenter().x - 500.f, motor->view.getCenter().y - 450.f);
        sprite.scale(0.8f,1.25f);
        
    }
    
}

void ControlState::HandleInput(){
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

                    if(idFrom ==1){
                        datagame->states.popState();
                    }else if(idFrom ==2){
                        datagame->states.addState(state_ptr(new OptionsState(this->datagame)));
                    }
                    
                    break;
            }
        }
    }
}

void ControlState::Update(const float &dt){
   
}

void ControlState::Render(const float &dt){

    motor->window.clear();

    motor->drawSprite(sprite);

    motor->window.display();
}