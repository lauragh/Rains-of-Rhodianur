#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

#define Max_options_menu 5 

class OptionsState: public State{
    private:

        GameData datagame;
        int optionSelected;
        sf::Font font;
        sf::Text optionsMenu[Max_options_menu];
        Motor2D *motor;
    
    public:
        OptionsState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveUp();
        void moveDown();
        int optionsPressed();
        void modificarSonido();
};