#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../motor2D/motor2D.h"

class Proyectil{
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f posicion;
    sf::Vector2f posicionInicial;
    int tipo;
    bool faceRight;
    std::string direccion;
    //colisiones
    sf::RectangleShape col;
    int tirador;

    float bottomCol;
    float leftCol;
    float rightCol;
    float topCol;

    std::vector<sf::Vector2i> cornerTiles;
    bool colision;

    Motor2D *motor;
   
    public:
    Proyectil(int, sf::Vector2f, bool, std::string, int);
    ~Proyectil();
    int getTipo();
    bool getColision(){return colision;}
    void setPosicion(sf::Vector2f);
    void Draw();
    void UpdatePos(float);
    int collisions();
    void updateBox();
};
