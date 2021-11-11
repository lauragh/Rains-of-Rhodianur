#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"

#define Max_options_menu 5 

class InventarioState: public State{
    private:

        GameData datagame;
        Motor2D *motor;
        sf::Sprite sprite;
        int objetoSeleccionado;
        sf::RectangleShape selector;
        std::vector <Object*> equiped;
        std::vector <sf::Sprite*> equipedSprite;
        std::vector <Object*> inventario;
        std::vector <sf::Sprite*> inventarioSprite;
        bool actualizar;
        sf::Sprite dineroJugador;
        sf::Sprite flechasJugador;
        sf::Sprite manaJugador;
        sf::Sprite vidaJugador;
        sf::Font fuente;
        sf::Text cantDineroJugador;
        sf::Text cantFlechasJugador;
        sf::Text cantVidaJugador;
        sf::Text cantManaJugador;
        
    
    public:
        InventarioState(GameData data);
        
        void Init();
        void HandleInput();
        void Update(const float &dt);
        void Render(const float &dt);

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        bool intercambiarObjeto();
        void pintar();
        std::string num2String(int num);
};