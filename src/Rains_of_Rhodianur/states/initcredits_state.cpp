#include <sstream>
#include <iostream>

#include "../states/initcredits_state.h"
#include "../states/mainmenu_state.h"
#include "../include/config.h"


InitCreditsState::InitCreditsState(GameData data): datagame(data){
    
}

void InitCreditsState::Init(){
    motor = Motor2D::Instance();
    motor->addTexture("BUGYSOFT", SPLASH_SCENE_BACKGROUND_FILEPATH);
    _background.setTexture(motor->getTexture("BUGYSOFT"));
    motor->addFont("Main Font", MAIN_FONT);
}

void InitCreditsState::HandleInput(){
    sf::Event event;

    while(motor->window.pollEvent(event)){
        if (sf::Event::Closed == event.type)
        {
            motor->window.close();
        }
    }
}

void InitCreditsState::Update(const float &dt){
    if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
    {
        datagame->states.addState(state_ptr(new MainMenuState(this->datagame)));
    }
}

void InitCreditsState::Render(const float &dt){
    motor->window.clear();

    motor->drawSprite(_background);

    motor->window.display();
}
