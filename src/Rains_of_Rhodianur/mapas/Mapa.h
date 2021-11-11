#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../motor2D/motor2D.h"
#include "tinyxml2.h"


using namespace tinyxml2;

//Esto genera un mapa, una vez solo
//el drawable y transformable los heredas de sfml
class Mapa : public sf::Drawable, public sf::Transformable
{
private:
    static Mapa* mapa;
    sf::Texture tile;
    Motor2D *motor;
public:

    void rellenartilesdanyinos();

    std::vector <int> tilesdanyinos;

    sf::VertexArray layer_fondo; //Nueva capa de fondo
    sf::VertexArray layer_intermedio; //Capa de fondo intermedio
    sf::VertexArray layer_normal;//Capa principal, donde interactúa el jugador principamente
    sf::VertexArray layer_frontal;//Capa cercana

    Mapa();
    ~Mapa();
    
    //Esta es la funcion que te caga el mapa y se guarda los datos del tmx
    void cargarMapaTMX(const char*);

    //Cargamos el mapa con los datos obtenidos del tmx que conseguimos en matrizDelMapa()
    //Vector2u: devuelve un 2int, int sin valores negativos
    bool load(sf::Vector2u tile_size, int*** nivel,unsigned int ancho, int numCapas/*, int numNivel*/);

    //El const despues del metodo indica que este metodo no va a cambiar los valores de las variables de clase
    //Como no es recomendable modificar el metodo padre del que hereda Draw, y tenemos que pintar las distintas capas del mapa por separado, haremos 2 métodos de dibujado del mapa
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawMap();
    void draw2();//Este dibuja solo la capa delantera

    void eliminarMapa();//Borras las matrices del mapa, para dibujar una zona diferente. También nos sirve para cuando muera el jugador y aparezca en el spawn

    //VARIABLES
    //Mapa de tiles, almacenamos todos los GIDs aqui.
    //De esta matriz muy probablemente dibujaremos 
    int*** tileArray;
    //Matriz de colisiones
    int** gitMatrix;

    //Ancho y alto del mapa
    int ancho;
    int alto;
    //Ancho y alto del tile
    int anchoTile;
    int altoTile;
    int numCapas;

    //getEnemyDat ==> Getter del vector de struct mencionado arriba
     struct enemyDat{
        int tipo;
        sf::Vector2f posicion;//Vector con X e Y
    };
    std::vector<enemyDat> enemigos;

    struct spawnDat{
        int id;
        sf::Vector2f posicion;
    };
    std::vector<spawnDat> spawns;

    struct objetoDat{
        
    };
    std::vector<objetoDat> objetos;

    //sf::Vector2f** posiciones; //Esto es la matriz de colisiones pero que los valores de posición estan/16.

    //Ruta del tmx. Vamos, entiendo que cada zona tendrá un tilemap diferente, por lo que habrá varias rutas
    std::string ruta_zona;
    
    //De aqui vamos leyendo linea a linea el archivo tmx
    XMLElement *data;

    
};
