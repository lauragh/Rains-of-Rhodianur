#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>


#include "../mapas/Mapa.h"
#include "../mapas/zonas.h"
#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../motor2D/interfaz.h"
#include "../motor2D/proyectil.h"
#include "../motor2D/motor2D.h"
#include "../player/player.h"


#include "../states/mainmenu_state.h"
#include "../states/pausemenu_state.h"
#include "../include/config.h"


class GameState: public State{

    public:

        static GameState* Instance(GameData data);
        static GameState* Instance();

        GameData datagame;
        zonas *zonactual;
        sf::Music music;
        player *jugador;
        bool musicaActiva;
        bool mapaBosque;
        bool mapaMontana;

        void readTxtandLoadObjects();
        std::vector<std::string> split(std::string separar, char separador);
        void cambioZona(int, int);
        void reaparecerCheckpoint();
        void cambioCancion(std::string nombre);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

    protected:

        GameState();
        GameState(GameData data);

        sf::Clock _clock;
        sf::Sprite _background;
        Interfaz *hud;
        Motor2D *motor;

        
        Proyectil *proyectil;
        std::vector<Proyectil*> proyectilesLanzados;
        sf::Clock *relojProyectil;
        sf::Clock *relojDisparo;


    private:

        static GameState* pinstance;

};