#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../motor2D/motor2D.h"

 
class InitCreditsState: public State{
    private:

        GameData datagame;

        Motor2D *motor;

        sf::Clock _clock;
        sf::Sprite _background;
    
    public:
        InitCreditsState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);
};
