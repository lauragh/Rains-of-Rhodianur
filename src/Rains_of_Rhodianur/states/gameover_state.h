#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

#define Max_gameover_menu 3
 
class GameOverState: public State{
    private:

        GameData datagame;
        int menuGameOverSelected;

        sf::Font font;
        sf::Text menuGameOver[Max_gameover_menu];
        Motor2D *motor;
    
    public:
        GameOverState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveUp();
        void moveDown();
        int menuGameOverPressed();
};