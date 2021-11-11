#pragma once

#include <SFML/Graphics.hpp>

#include "../npcs/object.h"
#include "../motor2D/interfaz.h"
#include "../motor2D/motor2D.h"




class player{
public:
    player(sf::Vector2u ImageCount, float switchTime, float speed, float jumpHeight, int x, int y);
    ~player();

    void Update(float deltaTime);
    void A_Update(int row, float deltaTime);
    void Draw(); 
    
    sf::Vector2f GetPosition(){return col.getPosition();}
    int getArrows(){return arrow;}
    int getPotiVida(){return potion_h;}
    int getPotiMana(){return potion_m;}
    bool getFace(){return faceRight;}
    bool getDisparo(){return disparo;}
    int getTipoDisparo(){return tipoDisparo;}

    void proyectilCollision();

    int respawn;
    void setIDrespawn();
    void setPositionRespawn(int);

    std::vector <int> tilesInvisibles;
    void rellenarTilesInvisibles();

    std::vector <int> tilesTiendas;
    void rellenarTilesTiendas();

    bool saltoEscalada;
    bool dobleSalto;
    bool dash;
    int contadorSaltos;

    sf::IntRect uvRect;

    void collisions();
    void updateBox();
    void updateAtackBox();
    void sideCollisions(std::string);
    void updownCollisions(float);
    void environmentCollisions();
    void atackBox();
    void atackCollisions();
    int getMoney();
    float getVida();
    float getVidaMax();
    float getMana();
    float getManaMax();
    void setVida(float vida);
    void setMana(float mana);
    void setMoney(int dinero);
    void setPotis(std::string tipo);
    void setArrow(int num);
    std::vector <Object*> getObjetosDisponibles();
    std::vector <Object*> getObjetosEquipados();
    std::vector <Object*> available;
    std::vector <Object*> equiped;
    void updateObjetosDisponibles(Object* objeto);
    std::string getAtaqueSecundario();
    void setAtaqueSecundario(std::string);
    float posX;
    float posY;

    //colisiones
    sf::RectangleShape col;
    sf::RectangleShape colatk;

    float bottomCol;
    float leftCol;
    float rightCol;
    float topCol;

    float bottomColatk;
    float leftColatk;
    float rightColatk;
    float topColatk;

    bool techo;
    std::string ataqueSecundarioSelected;
    int money;

    std::vector<sf::Vector2i> cornerTiles;
    std::vector<sf::Vector2i> cornerTilesAtk;
    Interfaz *info;

    float health;
    float t_health;
    float mana;
    float t_mana;
    bool death=false;
    float armadura=0;

private:
    sf::Sprite *sprite;
    sf::Texture texture;
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

    bool ataquePrincipal;
    bool ataqueSecundario;
    

    Motor2D *motor;


    float alto;
    float ancho;
    float left;
    float top;
    int alto_I;
    int ancho_I;
    int left_I;
    int top_I;

    unsigned int row;
    float speed;
    bool faceRight;
    bool canJump=false;
    bool canDash;
    bool agachado=false;
    bool hurt=false;
    
    

    sf::Vector2f velocity;
    float jumpHeight;

    bool disparo;
    int tipoDisparo;
    
    
    
    int potion_h;
    int potion_m;
    int arrow;



    //Relojes antispam
    sf::Clock *relojAtaquePrincipal;
    sf::Clock *relojAtaqueSecundario;
    sf::Clock *relojDaño;
    sf::Clock *relojCambioArma;
    sf::Clock *relojDash;
    sf::Clock *relojSuelo;
    sf::Clock *relojProyectil;
    sf::Clock *relojPegar;
    sf::Clock *relojDobleSalto;
    sf::Clock *relojPoti;

    //movimiento
    void controller();
    void keyboard();
    void mouse();

};
