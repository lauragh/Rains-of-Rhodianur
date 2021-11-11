
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../states/statemanager.h"
#include "../npcs/object.h"
#include "../motor2D/motor2D.h"

struct LoopStruct
{
    StateManager states;
    std::map<std::string, Object*> objects;
};

typedef std::shared_ptr<LoopStruct> GameData;

class Loop{

    public:

        Loop();
        ~Loop();
        //Metodo para inicializar el cambio de estados
        void loop_game();   

    private:

        GameData gamedata = std::make_shared<LoopStruct>();
        Motor2D *motor;
        sf::Clock clock;
        const float delta = 1.f/60.f; //FRAMERATE

        void init();

};