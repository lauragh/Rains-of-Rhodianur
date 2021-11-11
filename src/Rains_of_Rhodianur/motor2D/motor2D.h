#pragma once

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include <string>

class Motor2D {
    

    public:
        static Motor2D* Instance();

        void addTexture(std::string name, const std::string& rute);
        sf::Texture& getTexture(const std::string& name);
        void drawTexture();

        void addFont(std::string name, const std::string& rute);
        sf::Font& getFont( const std::string& name);
        void drawText(sf::Text);

        void drawSprite(sf::Sprite);
        void drawSprite(sf::Sprite*);
        void drawRectangleShape(sf::RectangleShape);

        void drawMap2(sf::VertexArray, sf::RenderStates);
        void setViewPlayerPos(float, float);
        void inicializarCamara(float x, float y);

        sf::RenderWindow window;
        sf::View view;

        bool debug;
        bool godmode;

    protected:
        Motor2D();
        ~Motor2D();

        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
        

    private:
        
        static Motor2D* pinstance;

};