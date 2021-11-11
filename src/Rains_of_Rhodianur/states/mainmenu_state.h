#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

class MainMenuState: public State{
    private:

        GameData datagame;
        int mainMenuSelected;

        sf::Font font;
        sf::Text mainMenu[Max_main_menu];
        Motor2D *motor;
    
    public:
        MainMenuState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveUp();
        void moveDown();
        int mainMenuPressed();
};
