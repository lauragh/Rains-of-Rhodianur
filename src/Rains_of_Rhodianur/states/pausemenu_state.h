#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

#define Max_pause_menu 4
 
class PauseMenuState: public State{
    private:

        GameData datagame;
        int menuPauseSelected;

        sf::Font font;
        sf::Text menuPause[Max_pause_menu];
        Motor2D *motor;
    
    public:
        PauseMenuState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveUp();
        void moveDown();
        int menuPausePressed();
};