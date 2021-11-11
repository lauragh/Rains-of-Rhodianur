
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../motor2D/motor2D.h"
#include "../motor2D/proyectil.h"

class Enemy{

    private:

        int health;
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;
        int alto;
        int ancho;

        sf::Vector2f velocity;
        std::string dir_sprite;

        sf::Sprite *sprite;
        sf::Texture texture;

        Motor2D *motor;

        int tipo;
        int posx;
        int posy;
        float speed;

        //relojes
        sf::Clock relojDisparo;
        sf::Clock relojProyectil;
        sf::Clock *relojAnimacion;
        sf::Clock *relojDuele;
        sf::Clock *relojTeleport;
        sf::Clock *relojChange;


        std::vector<Proyectil*> proyectilesLanzados;
        std::map<int, int> sprite_map;
        int row;
        bool faceRight;
        float deltaTime;

        //Crear enemigos

        void CreateEnemy1(int, int);
        void CreateEnemy2(int, int);
        void CreateEnemy3(int, int);
        void CreateEnemy4(int, int);
        void CreateEnemy5(int, int);
        void CreateEnemy6(int, int);
        void CreateEnemy7(int, int);
        void CreateEnemy8(int, int);
        void CreateEnemy9(int, int);

        void CreateBoss1(int, int);
        void CreateBoss2(int, int);

        //Inteligencia artificial

        void IAenemy1(float);
        void IAenemy2(float);
        void IAenemy3(float);
        void IAenemy4(float);
        void IAenemy5(float);
        void IAenemy6(float);
        void IAenemy7(float);
        void IAenemy8(float);
        void IAenemy9(float);

        void IABoss1(float);
        void IABoss2(float);

    public:

        Enemy();
        ~Enemy();
        Enemy(int, int, int);

        void Update(float deltaTime);

        std::vector<sf::Vector2i> cornerTiles;
        std::vector<sf::Vector2i> cornerTilesV1;
        std::vector<sf::Vector2i> cornerTilesV2;
        void collisions(bool);
        void updateBox();
        void updateBoxVision();
        void updateBoxVision2();
        void Animation(float,bool);


        void draw();
        void hit(int, int);

        std::string getSprite(){ return dir_sprite;}
        int getPosX(){ return posx;}
        int getPosY(){ return posy;}

        //colisiones
        sf::RectangleShape col;
        sf::RectangleShape col2;
        sf::RectangleShape col3;

        float bottomCol;
        float leftCol;
        float rightCol;
        float topCol;

        float bottomColPro;
        float leftColPro;
        float rightColPro;
        float topColPro;

        float bottomColPro2;
        float leftColPro2;
        float rightColPro2;
        float topColPro2;

        int damage;

        //cajas de colision del Jefe 1

        sf::RectangleShape colB1;
        sf::RectangleShape colB2;
        sf::RectangleShape colB3;
        sf::RectangleShape colB4;

        float bottomColB1;
        float leftColB1;
        float rightColB1;
        float topColB1;

        float bottomColB2;
        float leftColB2;
        float rightColB2;
        float topColB2;

        float bottomColB3;
        float leftColB3;
        float rightColB3;
        float topColB3;
        
        float bottomColB4;
        float leftColB4;
        float rightColB4;
        float topColB4;

        void updateBoxOrbitales();
        void orbitalesPlayerCollisions();

        int idPatron;

        sf::Texture textureB;
        sf::Sprite *spriteB1;
        sf::Sprite *spriteB2;
        sf::Sprite *spriteB3;
        sf::Sprite *spriteB4;
        
        void vidaEnemigos(int posX, int posY,int vidas);
        void updateVidaEnemigos(int vida);
        void moveVidaEnemigos(float x, float y);
        void setPositionVidaEnemigos(float x, float y);
        
    
        sf::RectangleShape marcoVida;
        sf::RectangleShape vidaActual;
        sf::Text labelVida;

        int vidaT;


};