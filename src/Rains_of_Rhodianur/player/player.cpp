#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "player.h"
#include "../motor2D/loop.h"
#include "../states/game_state.h"
#include "../states/gameover_state.h"
#include "../states/shop_state.h"
#include "../states/map_state.h"
#include "../states/inventario_state.h"



//Constructor de player, el primer cacho es todo dedicado inicializar la animacion
//El segundo cacho es para ya el personaje como tal, el tamaño, donde se coloca...
player::player(sf::Vector2u ImageCount, float switchTime, float speed, float jumpHeight, int x, int y)
{   
    relojAtaquePrincipal = new sf::Clock;
    relojAtaqueSecundario = new sf::Clock;
    relojDaño = new sf::Clock;
    relojCambioArma = new sf::Clock;
    relojDash = new sf::Clock;
    relojSuelo = new sf::Clock;
    relojProyectil = new sf::Clock;
    relojPegar = new sf::Clock;
    relojDobleSalto = new sf::Clock;
    relojPoti = new sf::Clock;

    rellenarTilesInvisibles();
    rellenarTilesTiendas();

    respawn = 0;
    saltoEscalada = false;
    dobleSalto = false;
    contadorSaltos = 0;

    this->imageCount = ImageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    GameState *game = GameState::Instance();

    motor = Motor2D::Instance();
    motor->addTexture("player_sprite1", "./resources/player_sprite1.png");

    texture = motor->getTexture("player_sprite1");

    ataquePrincipal = false;
    ataqueSecundario = false;
    ataqueSecundarioSelected = "Arco gastado";
    disparo = false;
    canDash = false;

    techo = false;
    this->speed=speed;
    this->jumpHeight=jumpHeight;
    row=0;
    faceRight=true;
    agachado=false;

    ancho=texture.getSize().x / float(imageCount.x);
    alto=texture.getSize().y / float(imageCount.y);

    this->sprite = new sf::Sprite(texture);

    left=0;
    top=0;

    //pasar a int porque no funciona el IntRect con float
    alto_I=alto;
    ancho_I=ancho;
    left_I=left;
    top_I=top;

    //sprite->setOrigin(ancho/2, alto/2);
    sprite->setTextureRect(sf::IntRect(left_I, top_I, ancho_I, alto_I));
    sprite->setPosition(x,y);
    sprite->setScale(0.4,0.4);

    
    col.setPosition(x+5,y);
    col.setSize(sf::Vector2f(58*(0.4), 96*(0.4)));
    col.setFillColor(sf::Color::Blue);

    //poniendo la informacion de interfaz y creandola
    
    money=0;
    potion_h=3;
    potion_m=3;
    arrow=3;

    equiped.push_back(game->datagame->objects["Hacha oxidada"]);
    equiped.push_back(game->datagame->objects["Arco gastado"]);
    equiped.push_back(game->datagame->objects["Fuego"]);
    equiped.push_back(game->datagame->objects["Hielo"]);
    equiped.push_back(game->datagame->objects["Sombrero de paja"]);
    equiped.push_back(game->datagame->objects["Camisa de leñador"]);
    equiped.push_back(game->datagame->objects["Guantes desgastados"]);
    equiped.push_back(game->datagame->objects["Pantalones rasgados"]);

    t_health=100;
    t_mana=100;
    for(int i=0;i<(int)equiped.size();i++){
        Object *aux=equiped[i];
        t_health=t_health+aux->getStats().health;
        t_mana=t_mana+aux->getStats().mana;
    }
    health=t_health;
    mana=t_mana;

    for(int i=0;i<(int)equiped.size();i++){
        Object *aux=equiped[i];
        armadura=armadura+aux->getStats().armour;
    }

    info=new Interfaz(sprite->getPosition(),health, t_health, mana, t_mana, money, potion_h, potion_m, arrow ,equiped, ataqueSecundarioSelected);

}

player::~player(){
    respawn=0;
    tilesInvisibles.clear();
    tilesTiendas.clear();
    saltoEscalada=false;
    uvRect=sf::IntRect();
    for(int i=0;i<(int)available.size();i++){
        available[i]=NULL;
    }
    available.clear();
    for(int i=0;i<(int)equiped.size();i++){
        equiped[i]=NULL;
    }
    equiped.clear();
    posX=0;
    posY=0;

    col=sf::RectangleShape();
    colatk=sf::RectangleShape();

    bottomCol=0;
    leftCol=0;
    rightCol=0;
    topCol=0;

    bottomColatk=0;
    leftColatk=0;
    rightColatk=0;
    topColatk=0;

    techo=false;

    money=0;

    cornerTiles.clear();
    cornerTilesAtk.clear();
    info=NULL;

    sprite=NULL;
    texture=sf::Texture();
    imageCount=sf::Vector2u();
    currentImage=sf::Vector2u();
    totalTime=0;
    switchTime=0;

    ataquePrincipal=false;
    ataqueSecundario=false;
    ataqueSecundarioSelected="";

    motor=NULL;

    alto=0;
    ancho=0;
    left=0;
    top=0;
    alto_I=0;
    ancho_I=0;
    left_I=0;
    top_I=0;

    row=0;
    speed=0;
    faceRight=false;
    canJump=false;
    canDash=false;
    agachado=false;
    hurt=false;
    death=false;
    armadura=0;

    velocity=sf::Vector2f();
    jumpHeight=0;

    disparo=false;
    tipoDisparo=0;
    
    health=0;
    t_health=0;
    mana=0;
    t_mana=0;
    potion_h=0;
    potion_m=0;
    arrow=0;

    relojAtaquePrincipal=NULL;
    relojAtaqueSecundario=NULL;
    relojDaño=NULL;
    relojCambioArma=NULL;
    relojDash=NULL;
    relojSuelo=NULL;
    relojProyectil=NULL;
    relojPegar=NULL;
    relojPoti=NULL;

}


//Este update mueve al personaje dependiendo de lo que le mande el jugador y llama a actualizar la animacion
void player::Update(float deltaTime){


        if(faceRight){

            col.setPosition(posX+5,posY);
            col.setSize(sf::Vector2f(58*(0.4), 96*(0.4)));
        }else{
            col.setPosition(posX+12,posY);
            col.setSize(sf::Vector2f(58*(0.4), 96*(0.4)));
        }



    armadura=0;
    for(int i=0;i<(int)equiped.size();i++){
        Object *aux=equiped[i];
        armadura=armadura+aux->getStats().armour;
    }
   
    velocity.y +=981.0f*deltaTime;  
    velocity.x *=0.1f;
    
   
        this->updateBox();
        updownCollisions(deltaTime);
    if(!death){      
        environmentCollisions();
            if(sf::Joystick::isConnected(0)){

                controller();

            } else {
            
                keyboard();
                mouse();
            } 
    }

    sprite->move((velocity.x*deltaTime),(velocity.y*deltaTime));
    col.move((velocity.x*deltaTime),(velocity.y*deltaTime));

    collisions();
    
    if(!death){
        if(ataquePrincipal){

            atackBox();
            float dt = 0.03;
            this->A_Update(row, dt);
        }else if(ataqueSecundario){
            float dt = 0.03;
            this->A_Update(row, dt);
        }else{
            if(hurt){
                if(faceRight){
                row=9;
                }else{
                    row=20;
                }
            }
            this->A_Update(row, deltaTime);
        }  
    }else{
        if(faceRight){
            row=7;
        }else{
            row=18;
        }
        agachado=false;
        this->A_Update(row, deltaTime);
    }

    info->update(sprite->getPosition().x, sprite->getPosition().y, velocity, deltaTime, health, t_health, mana, t_mana, money, this->potion_h, this->potion_m, arrow ,equiped, ataqueSecundarioSelected);
    
    posX = sprite->getPosition().x;
    posY = sprite->getPosition().y;
}

//Esto es basicamente la animacion, 
void player::A_Update(int row, float deltaTime){
    if(row!=7&&row!=18){
        agachado=false;
    }
    if((int) currentImage.y != row){
        currentImage.x = 0;
    }

    currentImage.y = row;
    totalTime += deltaTime;


    //control para cambiar de sprite respecto al switch time
    if(totalTime >= switchTime)
    {   if((currentImage.y==7||currentImage.y==18)&&agachado){
            currentImage.x = 3;
        }else{
            totalTime -= switchTime;
            currentImage.x++;

            if((currentImage.y==7||currentImage.y==18)&&currentImage.x==3){
            agachado=true;
            }
            if (ataqueSecundario && currentImage.x == 4){
               
                if((tipoDisparo==1&&arrow>0)||(tipoDisparo==8&&arrow>0)||(tipoDisparo==9&&arrow>0)){
                    disparo = true;
                    arrow--;
                    
                }  
                if((tipoDisparo!=0)&&(tipoDisparo!=1)&&(tipoDisparo!=8)&&(tipoDisparo!=9)){
                    disparo = true;
                }  
            }else{
                disparo = false;
            }
            
            if(currentImage.x >= imageCount.x&&!death)
            {  
                currentImage.x = 0;
                ataquePrincipal = false;
                ataqueSecundario = false;
            }
            if(currentImage.x >= imageCount.x&&death){
                currentImage.x = 5;
                //aqui poner estado de muerte final del juego
                GameState *game = GameState::Instance();
                game->datagame->states.addState(state_ptr(new GameOverState(game->datagame)),false);
            }
        }
        
    }
    top = currentImage.y * alto;

    //controlamos la orientacion del sprite
    
    left = currentImage.x * ancho;
    ancho = std::abs(ancho);
    

    alto_I=alto;
    ancho_I=ancho;
    left_I=left;
    top_I=top;


    sprite->setTextureRect(sf::IntRect(left_I, top_I, ancho_I, alto_I));
    sprite->setScale(0.4,0.4);
    
}

int player::getMoney(){
    return money;
}

void player::setMoney(int dinero){
    money = dinero;
}

void player::setPotis(std::string tipo){
    if(tipo == "v"){
        potion_h++;
    }
    else if( tipo == "m"){
        potion_m++;
    }
}

void player::setArrow(int num){
    arrow++;
}
float player::getVida(){
    return health;
}

float player::getVidaMax(){
    return t_health;
}

void player::setVida(float vida){
    health = vida;
}

float player::getMana(){
    return mana;
}

float player::getManaMax(){
    return t_mana;
}

void player::setMana(float mana){
    this->mana = mana;
}

std::vector <Object*> player::getObjetosDisponibles(){
    return available;

}

std::vector <Object*> player::getObjetosEquipados(){
    return equiped;

}

void player::updateObjetosDisponibles(Object* objeto){
    available.push_back(objeto);
}

void player::Draw(){
    
    if(motor->debug){
        motor->drawRectangleShape(colatk);
        motor->drawRectangleShape(col);
    }
    motor->drawSprite(*sprite);
}

void player::updateBox(){

    bottomCol = col.getPosition().y + col.getSize().y;
    leftCol = col.getPosition().x;
    rightCol = col.getPosition().x + col.getSize().x;
    topCol = col.getPosition().y;

    //4 esquinas

    sf::Vector2i topLeft(sf::Vector2i((int)leftCol/16, (int)topCol/16));
    sf::Vector2i topRight(sf::Vector2i((int)rightCol/16, (int)topCol/16));
    sf::Vector2i bottomLeft(sf::Vector2i((int)leftCol/16, (int)bottomCol/16));
    sf::Vector2i bottomRight(sf::Vector2i((int)rightCol/16, (int)bottomCol/16));

    //4 puntos intermedios

    /*sf::Vector2i midTop(sf::Vector2i((int)rightCol/16/2, (int)topCol/16));
    sf::Vector2i midLeft(sf::Vector2i((int)leftCol/16, (int)bottomCol/16/2));
    sf::Vector2i midRight(sf::Vector2i((int)rightCol/16, (int)bottomCol/16/2));
    sf::Vector2i midBottom(sf::Vector2i((int)rightCol/16/2, (int)bottomCol/16));*/

    cornerTiles.clear();

    cornerTiles.push_back(topLeft);
    if(std::find(cornerTiles.begin(), cornerTiles.end(), topRight) == cornerTiles.end()){ cornerTiles.push_back(topRight); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), bottomLeft) == cornerTiles.end()){ cornerTiles.push_back(bottomLeft); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), bottomRight) == cornerTiles.end()){ cornerTiles.push_back(bottomRight); }
    /*if(std::find(cornerTiles.begin(), cornerTiles.end(), midTop) == cornerTiles.end()){ cornerTiles.push_back(midTop); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), midLeft) == cornerTiles.end()){ cornerTiles.push_back(midLeft); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), midRight) == cornerTiles.end()){ cornerTiles.push_back(midRight); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), midBottom) == cornerTiles.end()){ cornerTiles.push_back(midBottom); }*/
    
}

void player::collisions(){


    if(!motor->godmode){
        GameState *game = GameState::Instance();



        bool me_Pegan=false;

        for(int j=0; j<(int)game->zonactual->enemylist.size(); j++){

            if(this->rightCol < game->zonactual->enemylist[j]->leftCol || this->leftCol > game->zonactual->enemylist[j]->rightCol ||
            this->topCol > game->zonactual->enemylist[j]->bottomCol || this->bottomCol < game->zonactual->enemylist[j]->topCol){

                game->zonactual->enemylist[j]->collisions(false);
            } else{

                game->zonactual->enemylist[j]->collisions(true);
                if(!ataquePrincipal){
                    hurt=true;
                    me_Pegan=true;
                }

                if(!ataquePrincipal&&relojDaño->getElapsedTime().asSeconds() >= 1&&health>0){
                    relojDaño->restart();
                    float daño_r=game->zonactual->enemylist[j]->damage-((game->zonactual->enemylist[j]->damage*armadura)/100);
                    daño_r=round(daño_r);
                    health=info->quitarVida(daño_r);
                }
                if(health<=0){
                    health=0;
                    death=true;
                }
            }
        }
        if(!me_Pegan){ hurt=false;}
    }
}

void player::setPositionRespawn(int respawn){
    GameState *game = GameState::Instance();
    int pos = -1;
    
    for (int i = 0; i < (int)game->zonactual->mapactual->spawns.size(); i++)
    {
        if (respawn == game->zonactual->mapactual->spawns[i].id)
        {
            pos = i;
        }
    }

    float x = game->zonactual->mapactual->spawns[pos].posicion.x; 
    float y = game->zonactual->mapactual->spawns[pos].posicion.y;

    sprite->setPosition(x,y);
    col.setPosition(x+5,y);
}

void player::controller(){

    float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);


    if(sf::Joystick::isButtonPressed(0,0) && canJump){

        canJump=false;
        velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
        if(faceRight){
           row=2;
        }else{
            row=13;
        }
    }

    if(y>90 && y<=100){

        if(faceRight){
           row=7;
        }else{
            row=18;
        }
        agachado=true;

    } else if(x>90 && x<=100){

        velocity.x += speed*1.5;

        row=1;
        faceRight=true;

    }else if(x>=-100 && x<-90){

        velocity.x -= speed*1.5;

        row=12;
        faceRight=false;

    }

    if(sf::Joystick::isButtonPressed(0,1) && relojAtaquePrincipal->getElapsedTime().asSeconds() >= 1){
        
        relojAtaquePrincipal->restart();
        if(faceRight){
           row=3;
        }else{
            row=14;
        }

        ataquePrincipal = true;
                
    } else if(sf::Joystick::isButtonPressed(0,2) && relojAtaqueSecundario->getElapsedTime().asSeconds() >= 1){

        relojAtaqueSecundario->restart();
        
        if(((ataqueSecundarioSelected == "Arco gastado") || (ataqueSecundarioSelected == "Arco de cazador") || (ataqueSecundarioSelected == "Ballesta"))){
            if(faceRight){
              row=5;
            }else{
                row=16;
            }
            tipoDisparo=1;
        }else if((ataqueSecundarioSelected == "Fuego") || (ataqueSecundarioSelected == "Fuego Alfa") || (ataqueSecundarioSelected == "Fuego Omega")){
            if(faceRight){
                row=4;
            }else{
                row=15;
            }
            if(ataqueSecundarioSelected == "Fuego"){
                tipoDisparo = 2;
            }else if (ataqueSecundarioSelected == "Fuego Alfa"){
               tipoDisparo = 3;
            }else if (ataqueSecundarioSelected == "Fuego Omega"){
                tipoDisparo = 4;
            }            
        }else if((ataqueSecundarioSelected == "Hielo") || (ataqueSecundarioSelected == "Hielo Alfa") || (ataqueSecundarioSelected == "Hielo Omega")){
            if(faceRight){
                row=6;
            }else{
                row=17;
            }
            if(ataqueSecundarioSelected == "Hielo"){
                tipoDisparo = 5;
            }else if (ataqueSecundarioSelected == "Hielo Alfa"){
               tipoDisparo = 6;
            }else if (ataqueSecundarioSelected == "Hielo Omega"){
                tipoDisparo = 7;
            }
        }
        
        ataqueSecundario = true;
        
    }

}

void player::keyboard(){


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && relojPoti->getElapsedTime().asSeconds() >= 0.5){
        relojPoti->restart();
        if(health < t_health){
            if(this->potion_h>0){
                this->health=info->usarPotiVida();
                this->potion_h--;
            }
        }
    }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && relojPoti->getElapsedTime().asSeconds() >= 0.5){
        relojPoti->restart();
        if(mana < t_mana){
            if(this->potion_m>0){
                this->mana=info->usarPotiMana();
                this->potion_m--;
            }
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && relojDash->getElapsedTime().asSeconds() >= 2 && dash){
        relojDash->restart();
        if(faceRight && canDash){

            canDash = false;
            this->velocity.x += speed*20;
            sideCollisions("derecha");
            
        } else if(!faceRight && canDash){

            canDash = false;
            this->velocity.x -= speed*20;
            sideCollisions("izquierda");
        }
    }

    //abrir mapa
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
        GameState *game = GameState::Instance();
        if(game->zonactual->idMapa == 2){
            game->datagame->states.addState(state_ptr(new MapState(game->datagame,game->zonactual->idMapa,game->mapaBosque)),false);
        }else if (game->zonactual->idMapa == 3)
        {
            game->datagame->states.addState(state_ptr(new MapState(game->datagame,game->zonactual->idMapa,game->mapaMontana)),false);
        }else {
            game->datagame->states.addState(state_ptr(new MapState(game->datagame,game->zonactual->idMapa,false)),false);
        } 
    }

    //abrir inventario
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
        GameState *game = GameState::Instance();
        game->datagame->states.addState(state_ptr(new InventarioState(game->datagame)),false);
    }



    //tienda 
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
        GameState *game = GameState::Instance();

        for(int i=0; i<(int)tilesTiendas.size(); i++){

            if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==tilesTiendas[i] ||
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==tilesTiendas[i]){

                    game->datagame->states.addState(state_ptr(new ShopState(game->datagame, tilesTiendas[i])),false);
                    break;
                }
        }


    }
    
    
    //saltar
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&canJump){

        sideCollisions("salto");
    }

    
    //agacharse
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

        if(faceRight){
            col.setPosition(posX+5,posY+20);
            col.setSize(sf::Vector2f(58*(0.4), 47*(0.4)));
            this->updateBox();
            row=7;
        }else{
            col.setPosition(posX+12,posY+20);
            this->updateBox();
            col.setSize(sf::Vector2f(58*(0.4), 47*(0.4)));
            row=18;
        }
        agachado=true;

    } else


    //movimiento derecha
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

        row=1;
        sideCollisions("derecha");
        faceRight=true;
    } else
        
    //movimiento izquierda
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

        row=12;
        sideCollisions("izquierda");
        faceRight=false;
    }
    else{
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::S)&&(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))&&(!sf::Keyboard::isKeyPressed(sf::Keyboard::D))&&(!sf::Keyboard::isKeyPressed(sf::Keyboard::A))&&!ataquePrincipal && !ataqueSecundario){

            if(faceRight){ row=10;} else{ row=21;}
        }
    }
    
}

void player::mouse(){

     if(sf::Mouse::isButtonPressed(sf::Mouse::Middle) && relojCambioArma->getElapsedTime().asSeconds() >= 0.5){
        relojCambioArma->restart();
        std::string newAtaqueSecundario;
        std::vector <Object*> secundarios;
        for(int i=0;i<(int)equiped.size();i++){
            Object *aux=equiped[i];
            if(aux->getType()=="Magia"||aux->getType()=="Proyectil"){
                secundarios.push_back(aux);
            }
        }
        for(int i=0;i<(int)secundarios.size();i++){
            Object *aux=secundarios[i];
            if(aux->getName()==ataqueSecundarioSelected){
                if(i==(int)secundarios.size()-1){
                    newAtaqueSecundario=secundarios[0]->getName();
                }else{
                    newAtaqueSecundario=secundarios[i+1]->getName();
                }
            }
        }/*
        for(int i=0;i<(int)equiped.size();i++){
            Object *aux=equiped[i];
            if(aux->getName()==ataqueSecundarioSelected){
                std::vector<Object*>::iterator it;
                it=std::find(equiped.begin(), equiped.end(), aux);
                equiped.erase(it);
            }
        } */
        ataqueSecundarioSelected=newAtaqueSecundario;
        
     }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && relojAtaquePrincipal->getElapsedTime().asSeconds() >= 0.5){
    
    relojAtaquePrincipal->restart();
    

    if(faceRight){
        row=3;
    }else{
        row=14;
    }

    ataquePrincipal = true;
            
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && relojAtaqueSecundario->getElapsedTime().asSeconds() >= 1){

        float consu_mana=0;
        for(int i=0;i<(int)equiped.size();i++){
            Object *aux=equiped[i];
            if(aux->getName()==ataqueSecundarioSelected){
                consu_mana=aux->getStats().amount_consume;
            }
        }

        relojAtaqueSecundario->restart();
        
        if(((ataqueSecundarioSelected == "Arco gastado") || (ataqueSecundarioSelected == "Arco de cazador") || (ataqueSecundarioSelected == "Ballesta"))){
            
            if(faceRight){
              row=5;
            }else{
                row=16;
            }
            if(ataqueSecundarioSelected == "Arco gastado"){
                tipoDisparo = 1;
            }else if (ataqueSecundarioSelected == "Arco de cazador"){
               tipoDisparo = 8;
            }else if (ataqueSecundarioSelected == "Ballesta"){
                tipoDisparo = 9;
            }  
            ataqueSecundario = true;
        }else if(((ataqueSecundarioSelected == "Fuego")&&(consu_mana<=info->getMana())) || ((ataqueSecundarioSelected == "Fuego Alfa")&&(consu_mana<=info->getMana())) || ((ataqueSecundarioSelected == "Fuego Omega")&&(consu_mana<=info->getMana()))){
            if(faceRight){
                row=4;
            }else{
                row=15;
            }
            if(ataqueSecundarioSelected == "Fuego"){
                tipoDisparo = 2;
            }else if (ataqueSecundarioSelected == "Fuego Alfa"){
               tipoDisparo = 3;
            }else if (ataqueSecundarioSelected == "Fuego Omega"){
                tipoDisparo = 4;
            }    
            this->mana=info->quitarMana(consu_mana); 
            ataqueSecundario = true;       
        }else if(((ataqueSecundarioSelected == "Hielo")&&(consu_mana<=info->getMana())) || ((ataqueSecundarioSelected == "Hielo Alfa")&&(consu_mana<=info->getMana())) || ((ataqueSecundarioSelected == "Hielo Omega")&&(consu_mana<=info->getMana()))){
            if(faceRight){
                row=6;
            }else{
                row=17;
            }
            if(ataqueSecundarioSelected == "Hielo"){
                tipoDisparo = 5;
            }else if (ataqueSecundarioSelected == "Hielo Alfa"){
               tipoDisparo = 6;
            }else if (ataqueSecundarioSelected == "Hielo Omega"){
                tipoDisparo = 7;
            }
            this->mana=info->quitarMana(consu_mana);  
            ataqueSecundario = true;
        }
        
        
        
        
    }

}

void player::sideCollisions(std::string direccion){

        GameState *game = GameState::Instance();

        bool invisible = true;


        if(direccion == "izquierda"){

            setIDrespawn();

            if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==251 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==251){

                //Cambio a montaña
                game->cambioZona(3, 1);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==252 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==252){

                //Cambio a aldea
                game->cambioZona(1, 2);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==253 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==253){

                //Cambio a montaña
                game->cambioZona(3, 3);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==254 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==254){

                //Cambio a montaña
                game->cambioZona(3, 2);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==266 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==266){

                //Cambio a bosque
                game->cambioZona(2, 4);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==265 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==265){

                //Cambio a montaña
                game->cambioZona(3, 8);

            }
            
            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                invisible = true;

                for(int i=0; i<(int)tilesInvisibles.size(); i++){

                    if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==tilesInvisibles[i] || 
                        game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==tilesInvisibles[i]){
                    
                            velocity.x -= speed*1.5;
                            invisible = false;
                            break;    
                    }

                }

                if(invisible){
                
                    velocity.x = 0;
                }

            } else { velocity.x -= speed*1.5;}
        }


        if(direccion == "derecha"){

            setIDrespawn();

            if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==250 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==250){

                //Cambio a bosque
                game->cambioZona(2, 1);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==258 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==258){

                //Cambio aldea
                game->cambioZona(1, 1);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==260 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==260){

                //Cambio bosque
                game->cambioZona(2, 2);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==261 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==261){

                //Cambio bosque
                game->cambioZona(2, 3);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==255 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==255){

                //Boss bosque
                game->cambioZona(4, 1);

            }

            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==264 || 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==264){

                //Boss montaña
                game->cambioZona(5, 1);

            }
                        
            else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                invisible = true;

                for(int i=0; i<(int)tilesInvisibles.size(); i++){

                    if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==tilesInvisibles[i] || 
                        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==tilesInvisibles[i]){
                    
                            velocity.x += speed*1.5;
                            invisible = false;
                            break;    
                    }

                }

                if(invisible){
                
                    velocity.x = 0;
                }
                    
            }else { velocity.x += speed*1.5;}
        }

        if(direccion == "salto"){

            if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                    velocity.x -= speed*1.5;

                for(int i=0; i<(int)tilesInvisibles.size(); i++){

                    if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==tilesInvisibles[i] || 
                        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==tilesInvisibles[i]){
                    
                            canJump=false;
                            velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
                            if(faceRight){ row=2; }else{ row=13; }
                            break;    
                    }

                }

            } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                    velocity.x += speed*1.5;

                for(int i=0; i<(int)tilesInvisibles.size(); i++){

                    if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==tilesInvisibles[i] || 
                        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==tilesInvisibles[i]){
                    
                            canJump=false;
                            velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
                            if(faceRight){ row=2; }else{ row=13; }
                            break;    
                    }

                }

            } else{

                    canJump=false;
                    velocity.y=-sqrtf(2.0f*981.0f*jumpHeight);
                    if(faceRight){ row=2; }else{ row=13; }

            }

            if(motor->godmode){
                canJump = true;
            }

        }
}

void player::updownCollisions(float deltaTime){

    GameState *game = GameState::Instance();

    bool entra = true;
    bool invisible = true;

        col.setFillColor(sf::Color::Blue);


        for(int i; i<(int)cornerTiles.size(); i++){

            if(this->cornerTiles[i].x<0 || this->cornerTiles[i].y<0 || 
            this->cornerTiles[i].x>game->zonactual->mapactual->ancho || this->cornerTiles[i].y>game->zonactual->mapactual->alto){

                entra = false;
            }
        }


if(entra){

        if(!techo && (game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0) ){

            invisible = true;

            for(int i=0; i<(int)tilesInvisibles.size(); i++){

                if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==tilesInvisibles[i] || 
                    game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==tilesInvisibles[i]){
                
                        invisible = false;
                        break;  
                }

            }

            if(invisible){

                techo = true;
                velocity.y = 0;
                //velocity.y +=981.0f*deltaTime;
                col.setFillColor(sf::Color::Red);

            }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

            invisible = true;

            for(int i=0; i<(int)tilesInvisibles.size(); i++){

                if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==tilesInvisibles[i] || 
                    game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==tilesInvisibles[i]){
                
                        invisible = false;
                        break; 
                }

            }

            if(invisible){

                canJump=true;
                canDash = true;
                techo = false;

                if((game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0)){

                    if((game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==0 && 
                    game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]==0)){

                        velocity.x += speed*1.5;
                        

                        if(!saltoEscalada){
                            velocity.y +=981.0f*deltaTime*7;
                            canJump = false;
                        }
                    }else {

                        velocity.y = 0;
                    }

                } else if((game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
                game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0)){

                    if((game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==0 && 
                    game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]==0)){

                        velocity.x -= speed*1.5;
                        
                        if(!saltoEscalada){
                            velocity.y +=981.0f*deltaTime*7;
                            canJump = false;
                        }

                    }else {
                        velocity.y = 0;
                    }
    
                } else {
                    velocity.y = 0;
                }
                
                col.setFillColor(sf::Color::Red);

            }
        }
}
}

void player::updateAtackBox(){

    bottomColatk = colatk.getPosition().y + colatk.getSize().y;
    leftColatk = colatk.getPosition().x;
    rightColatk = colatk.getPosition().x + colatk.getSize().x;
    topColatk = colatk.getPosition().y;

    sf::Vector2i topLeft(sf::Vector2i((int)leftColatk/16, (int)topColatk/16));
    sf::Vector2i topRight(sf::Vector2i((int)rightColatk/16, (int)topColatk/16));
    sf::Vector2i bottomLeft(sf::Vector2i((int)leftColatk/16, (int)bottomColatk/16));
    sf::Vector2i bottomRight(sf::Vector2i((int)rightColatk/16, (int)bottomColatk/16));

    cornerTilesAtk.clear();

    cornerTilesAtk.push_back(topLeft);
    if(std::find(cornerTilesAtk.begin(), cornerTilesAtk.end(), topRight) == cornerTilesAtk.end()){ cornerTilesAtk.push_back(topRight); }
    if(std::find(cornerTilesAtk.begin(), cornerTilesAtk.end(), bottomLeft) == cornerTilesAtk.end()){ cornerTilesAtk.push_back(bottomLeft); }
    if(std::find(cornerTilesAtk.begin(), cornerTilesAtk.end(), bottomRight) == cornerTilesAtk.end()){ cornerTilesAtk.push_back(bottomRight); }
    
}

void player::atackBox(){

    if(faceRight){

        colatk.setPosition(posX+(58*0.4)+5,posY);
    } else{

        colatk.setPosition(posX-(58*0.4)+15,posY);
    }


    
    colatk.setSize(sf::Vector2f(20, 96*(0.4)));
    colatk.setFillColor(sf::Color::Green);

    updateAtackBox();
    atackCollisions();

}

void player::atackCollisions(){

    GameState *game = GameState::Instance();

    for(int j=0; j<(int)game->zonactual->enemylist.size(); j++){

        if(this->rightColatk < game->zonactual->enemylist[j]->leftCol || this->leftColatk > game->zonactual->enemylist[j]->rightCol ||
        this->topColatk > game->zonactual->enemylist[j]->bottomCol || this->bottomColatk < game->zonactual->enemylist[j]->topCol){

            game->zonactual->enemylist[j]->collisions(false);
        } else{

            game->zonactual->enemylist[j]->collisions(true);
            int damage=0;
            if(relojPegar->getElapsedTime().asSeconds() >= 1){
                relojPegar->restart();
                for(int i=0;i<(int)equiped.size();i++){
                    Object *aux=equiped[i];
                    if(aux->getType()=="Principal"){
                        damage=aux->getStats().damage;
                    }
                }
                game->zonactual->enemylist[j]->hit(damage, 0);
            }
            

        }
    }

}

void player::environmentCollisions(){



if(!motor->godmode){

    GameState *game = GameState::Instance();
        if(game->zonactual->idMapa!=1){

    int entra = true;

        for(int i; i<(int)cornerTiles.size(); i++){

            if(this->cornerTiles[i].x<0 || this->cornerTiles[i].y<0 || 
            this->cornerTiles[i].x>game->zonactual->mapactual->ancho || this->cornerTiles[i].y>game->zonactual->mapactual->alto){

                entra = false;
            }
        }


if(entra){

    bool hit = false;

        int ArI = game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x];
        int ArD = game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x];
        int AbI = game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x];
        int AbD = game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x];

        for(int i=0; i<(int)game->zonactual->mapactual->tilesdanyinos.size(); i++){

            if(ArI==game->zonactual->mapactual->tilesdanyinos[i]){

                hit = true;
                break;
            } else if(ArD==game->zonactual->mapactual->tilesdanyinos[i]){

                hit = true;
                break;
            } else if(AbI==game->zonactual->mapactual->tilesdanyinos[i]){

                hit = true;
                break;
            } else if(AbD==game->zonactual->mapactual->tilesdanyinos[i]){

                hit = true;
                break;
            }
        }

        if(hit){

            if( relojSuelo->getElapsedTime().asSeconds() >= 3){
                
                relojSuelo->restart();
                health = info->quitarVida(10);
            }
            if(health<=0){
                health=0;
                death=true;
            }

        }
}
}
}
}

void player::proyectilCollision(){

if(!motor->godmode){

    if( relojProyectil->getElapsedTime().asSeconds() >= 1){
            relojProyectil->restart();
        health=info->quitarVida(7);
    }
    if(health<=0){
        health=0;
        death=true;
    }
}
}

void player::rellenarTilesInvisibles(){

    //tiles tiendas

    tilesInvisibles.push_back(257);
    tilesInvisibles.push_back(262);
    tilesInvisibles.push_back(263);
    tilesInvisibles.push_back(268);
    tilesInvisibles.push_back(269);

    //tiles checkpoints bosque

    tilesInvisibles.push_back(500);
    tilesInvisibles.push_back(501);
    tilesInvisibles.push_back(502);
    tilesInvisibles.push_back(503);

    //tiles checkpoints montanya

    tilesInvisibles.push_back(504);
    tilesInvisibles.push_back(505);
    tilesInvisibles.push_back(506);
    tilesInvisibles.push_back(507);

    tilesInvisibles.push_back(14250);

}

void player::rellenarTilesTiendas(){

    //tiles tiendas

    tilesTiendas.push_back(257);
    tilesTiendas.push_back(262);
    tilesTiendas.push_back(263);
    tilesTiendas.push_back(268);
    tilesTiendas.push_back(269);

}

void player::setIDrespawn(){

    GameState *game = GameState::Instance();


    if(game->zonactual->idMapa==2){

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==500 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==500){

                respawn = 500;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==501 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==501){

                respawn = 501;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==502 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==502){

                respawn = 502;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==503 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==503){

                respawn = 503;
        }
    }

    if(game->zonactual->idMapa==3){

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==504 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==504){

                respawn = 504;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==505 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==505){

                respawn = 505;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==506 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==506){

                respawn = 506;
        } else if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]==507 ||
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]==507){

                respawn = 507;
        }

    }

}

