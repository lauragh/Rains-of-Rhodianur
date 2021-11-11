#pragma once

#include <SFML/Graphics.hpp>
#include "../npcs/object.h"
#include "../motor2D/motor2D.h"

class Interfaz{
    
   private:
        sf::Sprite pocionVida;
        sf::Sprite pocionMana;
        sf::Sprite armaP;
        sf::Sprite armaS;
        sf::Sprite dinero;
        sf::Sprite flechas;
        sf::Texture texture;
        sf::View view;
        sf::RectangleShape marco;
        sf::RectangleShape marco2;
        sf::RectangleShape vidaTotal;
        sf::RectangleShape manaTotal;
        sf::RectangleShape vida;
        sf::RectangleShape mana;
        sf::RectangleShape armadura;
        sf::Text label;
        sf::Text label2;
        sf::Text label3;
        sf::Font fuente;
        sf::Text numVidas;
        sf::Text numMana;
        sf::Text cantMonedas;
        sf::Text numFlechas;
        float ptosVida;
        float ptosMana;
        float ptosArmadura;
        float vidaT;
        float manaT;
        double maxptosVidaPixel;
        double maxManaPixel;
        int numPotiVida;
        int numPotiMana;
        int cantDinero;
        int cantFlechas;
        

        Motor2D *motor;

    public:
        Interfaz();
        ~Interfaz();
        Interfaz(sf::Vector2f position, float puntosVida, float puntosTotalV, float puntosMana, float puntosTotalM, int cantDinero, int numPotiVida, int numPotiMana, int cantFlechas, std::vector <Object*> equipado, std::string ataqueSecundarioSelected);
        void update(float posX, float posY, sf::Vector2f velocity, float deltaTime, float puntosVida, float puntosTotalV, float puntosMana, float puntosTotalM, int cantDinero, int numPotiVida, int numPotiMana, int cantFlechas, std::vector <Object*> equipado, std::string ataqueSecundarioSelected);
        void createView(float x, float y);
        void setView(float x, float y);
        sf::Vector2f getView();
        void createBarras();
        void createArmadura();
        void createArmaP(int posArmaPY, int posArmaPX);
        void createArmaS(int posArmaSY, int posArmaSX);
        void createPociones();
        void createDinero();
        void createFlechas();
        void draw();
        void setNumPoti(int numPoti, sf::Sprite pocion, char tipo);
        void setPuntos(float puntos, float puntosTotal, sf::RectangleShape barra, char tipo);
        void setDinero(int cantDinero);
        void setFlechas(int cantFlechas);
        void setArmadura(float ptosArmadura);
        void setArmaP(int posX, int posY);
        void setArmaS(int posX, int posY);
        float quitarVida(float danoRecibido);
        float quitarMana(float manaConsumido);
        float sumarVida(float danoRecibido);
        float sumarMana(float manaConsumido);
        void setVida(float puntosVida);
        void setMana(float puntosMana);
        float usarPotiVida();
        float usarPotiMana();
        void moverInterfaz(float x, float y);
        void setInterfaz(float x, float y);
        float getMana();
        std::string ataqueSecundarioSelected;
};