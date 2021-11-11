#pragma once

#include "../states/state.h"
#include "../motor2D/loop.h"
#include "../include/config.h"
#include "../motor2D/motor2D.h"
 
class ShopState: public State{
    private:

        GameData datagame;
        Motor2D *motor;
        sf::Text label;
        sf::Text labelVida;
        sf::Text aumentoVida;
        sf::Text labelArmadura;
        sf::Text aumentoArmadura;
        sf::Text labelMana;
        sf::Text aumentoMana;
        sf::Text labelDanio;
        sf::Text aumentoDanio;
        sf::Text cantVida;
        sf::Text cantArmadura;
        sf::Text cantMana;
        sf::Sprite tiendaBG;
        sf::Sprite dineroJugador;
        sf::Font fuente;
        sf::Text cantDineroJugador;
        std::vector <sf::Text> costeObjetos;
        std::vector <sf::Sprite> monedasCoste;
        std::vector <sf::Text> optionsTienda;
        sf::RectangleShape selector;
        int objetoSeleccionado;
        int idTienda;
        std::vector <sf::Sprite> sprites;
        int cont;
        std::string nombre;
    
    public:
        ShopState(GameData data, int idTienda);
        std::vector <Object*> objetosTienda;
        std::vector <Object> objetosActuales;

        
        void Init();
        void HandleInput();
        void addTienda(sf::Sprite sprite, std::vector<std::string> tipo, int idTienda);
        void Update(const float &dt);
        void updateTienda();
        void Render(const float &dt);
        void moveLeft();
        void moveRight();
        void setEstadisticas();
        int objetoSeleccionadoPressed();
        std::string num2String(int num);
        void comprar();
};
