
#include "../mapas/zonas.h"

zonas::zonas(){}
zonas::~zonas(){
    pathmap=NULL;
    
     for(int i=0; i<totalenemylvl; i++){
        delete enemylist[i];
        enemylist[i]=NULL;
    }
    enemylist = std::map<int, Enemy*>();
    totalenemylvl=0;
    idMapa = 0;
    mapactual = NULL;
}

void zonas::crearZona(int numzona){

    switch (numzona) {
    
        case 1:
            pathmap = "resources/aldea.tmx";
            idMapa = 1;
            mapactual = new Mapa();
            mapactual->cargarMapaTMX(pathmap);
            mapactual->load(sf::Vector2u(16,16), mapactual->tileArray, mapactual->ancho, mapactual->numCapas);
            totalenemylvl = mapactual->enemigos.size();
            enemylist.clear();

            for(int i=0; i<totalenemylvl; i++){

                enemylist[i] = new Enemy(mapactual->enemigos[i].tipo, mapactual->enemigos[i].posicion.x, mapactual->enemigos[i].posicion.y);
            }

            break;

        case 2:

            pathmap = "resources/bosque.tmx";
            idMapa = 2;
            mapactual = new Mapa();
            mapactual->cargarMapaTMX(pathmap);
            mapactual->load(sf::Vector2u(16,16), mapactual->tileArray, mapactual->ancho, mapactual->numCapas);
            totalenemylvl = mapactual->enemigos.size();
            enemylist.clear();

            for(int i=0; i<totalenemylvl; i++){

                enemylist[i] = new Enemy(mapactual->enemigos[i].tipo, mapactual->enemigos[i].posicion.x, mapactual->enemigos[i].posicion.y);
            }

            break;

        case 3:

            pathmap = "resources/montaña.tmx";
            idMapa = 3;
            mapactual = new Mapa();
            mapactual->cargarMapaTMX(pathmap);
            mapactual->load(sf::Vector2u(16,16), mapactual->tileArray, mapactual->ancho, mapactual->numCapas);
            totalenemylvl = mapactual->enemigos.size();
            enemylist.clear();

            for(int i=0; i<totalenemylvl; i++){

                enemylist[i] = new Enemy(mapactual->enemigos[i].tipo, mapactual->enemigos[i].posicion.x, mapactual->enemigos[i].posicion.y);
            }

            break;

        case 4:

            pathmap = "resources/boss_bosque.tmx";
            idMapa = 4;
            mapactual = new Mapa();
            mapactual->cargarMapaTMX(pathmap);
            mapactual->load(sf::Vector2u(16,16), mapactual->tileArray, mapactual->ancho, mapactual->numCapas);
            totalenemylvl = mapactual->enemigos.size();
            enemylist.clear();

            for(int i=0; i<totalenemylvl; i++){

                enemylist[i] = new Enemy(mapactual->enemigos[i].tipo, mapactual->enemigos[i].posicion.x, mapactual->enemigos[i].posicion.y);
            }

            break;

            case 5:

            pathmap = "resources/boss_montaña.tmx";
            idMapa = 5;
            mapactual = new Mapa();
            mapactual->cargarMapaTMX(pathmap);
            mapactual->load(sf::Vector2u(16,16), mapactual->tileArray, mapactual->ancho, mapactual->numCapas);
            totalenemylvl = mapactual->enemigos.size();
            enemylist.clear();

            for(int i=0; i<totalenemylvl; i++){

                enemylist[i] = new Enemy(mapactual->enemigos[i].tipo, mapactual->enemigos[i].posicion.x, mapactual->enemigos[i].posicion.y);
            }

            break;
    
        default:
            break;
    }

}