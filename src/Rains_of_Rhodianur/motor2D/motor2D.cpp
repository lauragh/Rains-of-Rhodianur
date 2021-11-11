#include "../motor2D/motor2D.h"

Motor2D* Motor2D::pinstance = 0;

Motor2D* Motor2D::Instance(){

    if(pinstance == 0){

        pinstance = new Motor2D();
    }

    return pinstance;
}


Motor2D::Motor2D(){
    debug = false;
    window.create(sf::VideoMode(1280, 720), "Rains of Rhodianur");
    window.setFramerateLimit(60);
}


Motor2D::~Motor2D(){
    
}


void Motor2D::addTexture(std::string name, const std::string& rute)
{
    sf::Texture texture;
    
    if(texture.loadFromFile(rute))
    {
        this->textures[name] = texture;
    }else{
        std::cerr << "Error cargando la imagen sprites.png";
    }
}

sf::Texture &Motor2D::getTexture(const std::string& name)
{
    return this->textures.at(name);
}

void Motor2D::addFont(std::string nombre,const std::string& rute)
{
    sf::Font font;
    
    if(font.loadFromFile(rute))
    {
        this->fonts[nombre] = font;
    }
}

sf::Font &Motor2D::getFont(const std::string& name)
{
    return this->fonts.at(name);
}

void Motor2D::drawText(sf::Text text){
    window.draw(text);
}

void Motor2D::drawSprite(sf::Sprite sprite){
    window.draw(sprite);
}

void Motor2D::drawSprite(sf::Sprite *sprite){
    window.draw(*sprite);
}

void Motor2D::drawMap2(sf::VertexArray vertex, sf::RenderStates render){
    window.draw(vertex, render);
}

void Motor2D::drawRectangleShape(sf::RectangleShape rectangle){
    window.draw(rectangle);
}

void Motor2D::setViewPlayerPos(float x, float y){
    view.setCenter(x,y);

}

// void Motor2D::inicializarCamara(float x, float y){
//     view.setCenter(x,y);
//     view.zoom(0.55);
//     window.setView(view);
// }




