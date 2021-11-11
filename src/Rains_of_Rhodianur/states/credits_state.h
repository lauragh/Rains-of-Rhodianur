#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

class CreditsState: public State{
    private:

        GameData datagame;

        sf::Font font;
        sf::Text creditsTitle[Max_credits];
        Motor2D *motor;
    
    public:
        CreditsState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveUp();
        void moveDown();
};
