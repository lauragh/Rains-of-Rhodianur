#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

#define Max_options_menu 5 

class MapState: public State{
    private:

        GameData datagame;
        sf::Sprite sprite;
        Motor2D *motor;
        int zonaMapa;
        bool estaComprado;
    
    public:
        MapState(GameData data, int, bool);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);
};