
#include "enemy.h"
#include "../states/game_state.h"
#include <stdlib.h>
#include <time.h>


Enemy::Enemy(){}

Enemy::~Enemy(){
    health=0;
    imageCount = sf::Vector2u();
    currentImage = sf::Vector2u();
    totalTime=0;
    switchTime=0;
    alto=0;
    ancho=0;
    velocity=sf::Vector2f();
    dir_sprite="";
    sprite=NULL;
    texture= sf::Texture();
    motor=NULL;
    tipo=0;
    posx=0;
    posy=0;
    speed=0;
    relojDisparo=sf::Clock();
    relojProyectil=sf::Clock();
    relojAnimacion=NULL;
    relojDuele=NULL;
    for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
        delete proyectilesLanzados[i];
    }
    proyectilesLanzados.clear();
    sprite_map.clear();
    row=0;
    faceRight=false;
    deltaTime=0;
    cornerTiles.clear();
    cornerTilesV1.clear();
    cornerTilesV2.clear();

    col=sf::RectangleShape();
    col2=sf::RectangleShape();
    col3=sf::RectangleShape();
    colB1=sf::RectangleShape();
    colB2=sf::RectangleShape();
    colB3=sf::RectangleShape();
    colB4=sf::RectangleShape();

    bottomColB1=0;
    leftColB1=0;
    rightColB1=0;
    topColB1=0;

    bottomColB2=0;
    leftColB2=0;
    rightColB2=0;
    topColB2=0;

    bottomColB3=0;
    leftColB3=0;
    rightColB3=0;
    topColB3=0;
        
    bottomColB4=0;
    leftColB4=0;
    rightColB4=0;
    topColB4=0;

    bottomCol=0;
    leftCol=0;
    rightCol=0;
    topCol=0;

    bottomColPro=0;
    leftColPro=0;
    rightColPro=0;
    topColPro=0;

    bottomColPro2=0;
    leftColPro2=0;
    rightColPro2=0;
    topColPro2=0;

    damage=0;

    marcoVida=sf::RectangleShape();
    vidaActual=sf::RectangleShape();
    labelVida=sf::Text();
    vidaT=0;

    idPatron = 0;

    textureB = sf::Texture();
    spriteB1 = NULL;
    spriteB2 = NULL;
    spriteB3 = NULL;
    spriteB4 = NULL;
    
}

Enemy::Enemy(int type, int x, int y){

    this->velocity.x = 0;
    this->velocity.y = 0;
    this->posx = x;
    this->posy = y;
    this->tipo = type;
    relojAnimacion = new sf::Clock;
    relojDuele = new sf::Clock;
    this->faceRight=false;

    switch (type){

        case 1: CreateEnemy1(x, y);
            break;
        case 2: CreateEnemy2(x, y);
            break;
        case 3: CreateEnemy3(x, y);
            break;
        case 4: CreateEnemy4(x, y);
            break;
        case 5: CreateEnemy5(x, y);
            break;
        case 6: CreateEnemy6(x, y);
            break;
        case 7: CreateEnemy7(x, y);
            break;
        case 8: CreateEnemy8(x, y);
            break;
        case 9: CreateEnemy9(x, y);
            break;
        case 10: CreateBoss1(x,y);
            break;
        case 11: CreateBoss2(x,y);
            break;

    }

}

void Enemy::draw(){

    //GameState *game = GameState::Instance();

    if(motor->debug){

        motor->drawRectangleShape(col3);
        motor->drawRectangleShape(col2);
        motor->drawRectangleShape(col);

        motor->drawRectangleShape(colB1);
        motor->drawRectangleShape(colB2);
        motor->drawRectangleShape(colB3);
        motor->drawRectangleShape(colB4);

    }

    //Pintar los proyectiles lanzados
    for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
      proyectilesLanzados[i]->Draw();
    }

    motor->drawSprite(*sprite);
    motor->drawRectangleShape(marcoVida);
    motor->drawRectangleShape(vidaActual);
    motor->drawText(labelVida);

    motor->drawRectangleShape(colB1);
    motor->drawRectangleShape(colB2);
    motor->drawRectangleShape(colB3);
    motor->drawRectangleShape(colB4);

    /*if(game->zonactual->idMapa==4){

        motor->drawSprite(*spriteB1);
        motor->drawSprite(*spriteB2);
        motor->drawSprite(*spriteB3);
        motor->drawSprite(*spriteB4);
    }*/

}

void Enemy::updateBox(){

    bottomCol = col.getPosition().y + col.getSize().y;
    leftCol = col.getPosition().x;
    rightCol = col.getPosition().x + col.getSize().x;
    topCol = col.getPosition().y;

    sf::Vector2i topLeft(sf::Vector2i((int)leftCol/16, (int)topCol/16));
    sf::Vector2i topRight(sf::Vector2i((int)rightCol/16, (int)topCol/16));
    sf::Vector2i bottomLeft(sf::Vector2i((int)leftCol/16, (int)bottomCol/16));
    sf::Vector2i bottomRight(sf::Vector2i((int)rightCol/16, (int)bottomCol/16));

    cornerTiles.clear();

    cornerTiles.push_back(topLeft);
    if(std::find(cornerTiles.begin(), cornerTiles.end(), topRight) == cornerTiles.end()){ cornerTiles.push_back(topRight); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), bottomLeft) == cornerTiles.end()){ cornerTiles.push_back(bottomLeft); }
    if(std::find(cornerTiles.begin(), cornerTiles.end(), bottomRight) == cornerTiles.end()){ cornerTiles.push_back(bottomRight); }
    
}

void Enemy::updateBoxVision(){

    bottomColPro = col2.getPosition().y + col2.getSize().y;
    leftColPro = col2.getPosition().x;
    rightColPro = col2.getPosition().x + col2.getSize().x;
    topColPro = col2.getPosition().y;

    sf::Vector2i topLeftPro(sf::Vector2i((int)leftColPro/16, (int)topColPro/16));
    sf::Vector2i topRightPro(sf::Vector2i((int)rightColPro/16, (int)topColPro/16));
    sf::Vector2i bottomLeftPro(sf::Vector2i((int)leftColPro/16, (int)bottomColPro/16));
    sf::Vector2i bottomRightPro(sf::Vector2i((int)rightColPro/16, (int)bottomColPro/16));

    cornerTilesV1.clear();

    cornerTilesV1.push_back(topLeftPro);
    if(std::find(cornerTilesV1.begin(), cornerTilesV1.end(), topRightPro) == cornerTilesV1.end()){ cornerTilesV1.push_back(topRightPro); }
    if(std::find(cornerTilesV1.begin(), cornerTilesV1.end(), bottomLeftPro) == cornerTilesV1.end()){ cornerTilesV1.push_back(bottomLeftPro); }
    if(std::find(cornerTilesV1.begin(), cornerTilesV1.end(), bottomRightPro) == cornerTilesV1.end()){ cornerTilesV1.push_back(bottomRightPro); }
    
}

void Enemy::updateBoxVision2(){

    bottomColPro2 = col3.getPosition().y + col3.getSize().y;
    leftColPro2 = col3.getPosition().x;
    rightColPro2 = col3.getPosition().x + col3.getSize().x;
    topColPro2 = col3.getPosition().y;

    sf::Vector2i topLeftPro2(sf::Vector2i((int)leftColPro2/16, (int)topColPro2/16));
    sf::Vector2i topRightPro2(sf::Vector2i((int)rightColPro2/16, (int)topColPro2/16));
    sf::Vector2i bottomLeftPro2(sf::Vector2i((int)leftColPro2/16, (int)bottomColPro2/16));
    sf::Vector2i bottomRightPro2(sf::Vector2i((int)rightColPro2/16, (int)bottomColPro2/16));

    cornerTilesV2.clear();

    cornerTilesV2.push_back(topLeftPro2);
    if(std::find(cornerTilesV2.begin(), cornerTilesV2.end(), topRightPro2) == cornerTilesV2.end()){ cornerTilesV2.push_back(topRightPro2); }
    if(std::find(cornerTilesV2.begin(), cornerTilesV2.end(), bottomLeftPro2) == cornerTilesV2.end()){ cornerTilesV2.push_back(bottomLeftPro2); }
    if(std::find(cornerTilesV2.begin(), cornerTilesV2.end(), bottomRightPro2) == cornerTilesV2.end()){ cornerTilesV2.push_back(bottomRightPro2); }
    
}

void Enemy::collisions(bool b){
    
    if(b){
        this->col.setFillColor(sf::Color::Red);
    }

    else {this->col.setFillColor(sf::Color::Blue);}



}

void Enemy::Update(float deltaTime){
    this->deltaTime=deltaTime;
    switch(this->tipo){

        case 1: IAenemy1(deltaTime);
            break;
        case 2: IAenemy2(deltaTime);
            break;
        case 3: IAenemy3(deltaTime);
            break;
        case 4: IAenemy4(deltaTime);
            break;
        case 5: IAenemy5(deltaTime);
            break;
        case 6: IAenemy6(deltaTime);
            break;
        case 7: IAenemy7(deltaTime);
            break;
        case 8: IAenemy8(deltaTime);
            break;
        case 9: IAenemy9(deltaTime);
            break;
        case 10: IABoss1(deltaTime);
            break;
        case 11: IABoss2(deltaTime);
            break;
    }

}

//enemigo que se MUEVE en HORIZONTAL entre 2 PUNTOS en el SUELO
void Enemy::CreateEnemy1(int x, int y){

    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("goblin_sprite", "resources/goblin.png");
    this->texture = motor->getTexture("goblin_sprite");
    this->sprite = new sf::Sprite(texture);

    this->row=1;
    this->sprite_map.insert(std::pair<int,int>(0,3));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=32;
    this->alto=48;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+8,y);
    this->col.setSize(sf::Vector2f(20, 36));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.x += speed*1.5;
    
    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy1(float deltaTime){

    velocity.y +=981.0f*deltaTime;
    this->updateBox();

    GameState *game = GameState::Instance();

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

            velocity.y = 0;

        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                this->velocity.x = 0;
                this->velocity.x += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.x = 0;
                this->velocity.x -= speed*1.5;
        }
    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se MUEVE en HORIZONTAL entre 2 PUNTOS en el AIRE
void Enemy::CreateEnemy2(int x, int y){
                
    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo_sprite", "resources/ojo.png");
    this->texture = motor->getTexture("ojo_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=0;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+13,y+5);
    this->col.setSize(sf::Vector2f(20, 28));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.x += speed*1.5;
    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy2(float deltaTime){

    this->updateBox();

    GameState *game = GameState::Instance();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                this->velocity.x = 0;
                this->velocity.x += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.x = 0;
                this->velocity.x -= speed*1.5;
        }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se mueve en VERTICAL entre 2 puntos en el AIRE
void Enemy::CreateEnemy3(int x, int y){
                
    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo2_sprite", "resources/ojo.png");
    this->texture = motor->getTexture("ojo2_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=0;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+13,y+5);
    this->col.setSize(sf::Vector2f(20, 28));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.y += speed*1.5;
    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy3(float deltaTime){

    this->updateBox();

    GameState *game = GameState::Instance();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){

                this->velocity.y = 0;
                this->velocity.y += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.y = 0;
                this->velocity.y -= speed*1.5;
        }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo ESTATICO que DISPARA hacia la DERECHA
void Enemy::CreateEnemy4(int x, int y){
                
    this->speed = 0.0f;
    this->damage = 10;
    this->health = 20;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("hongo_sprite", "resources/hongo.png");
    this->texture = motor->getTexture("hongo_sprite");
    this->sprite = new sf::Sprite(texture);

    this->sprite_map.insert(std::pair<int,int>(0,3));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,7));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));
    this->row=1;

    this->ancho=48;
    this->alto=48;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x,y);
    this->col.setSize(sf::Vector2f(24, 36));
    this->col.setFillColor(sf::Color::Blue);
    this->col2.setPosition(x+24,y);
    this->col2.setSize(sf::Vector2f(80, 36));
    this->col2.setFillColor(sf::Color::Green);
    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy4(float deltaTime){

    velocity.y +=981.0f*deltaTime;
    this->updateBox();
    this->updateBoxVision();

    GameState *game = GameState::Instance();

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

            velocity.y = 0;

        }


        if(this->rightColPro < game->jugador->leftCol || this->leftColPro > game->jugador->rightCol ||
        this->topColPro > game->jugador->bottomCol || this->bottomColPro < game->jugador->topCol){

            this->col2.setFillColor(sf::Color::Green);

        } else{

            this->col2.setFillColor(sf::Color::Red);

            //AQUI HAY QUE TIRAR UN PROYECTIL
            //Disparar
            sf::Vector2f posEnemy = sf::Vector2f(posx, posy);
            if(relojDisparo.getElapsedTime().asSeconds() >= 1.5){
                relojDisparo.restart();
                Proyectil *proyectil= new Proyectil(2, posEnemy, true, "derecha",2);
                proyectilesLanzados.push_back(proyectil);
            }
            

        }
        //Posicion de los proyectiles
            if(relojProyectil.getElapsedTime().asMilliseconds() >= 20){
               relojProyectil.restart();
                for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
                    proyectilesLanzados[i]->UpdatePos(deltaTime);
                    if(proyectilesLanzados[i]->getColision()){
                        proyectilesLanzados.erase(proyectilesLanzados.begin() + i);
                    }
                }
            }
        faceRight=true;

    row=0;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

    
}

//enemigo ESTATICO que DISPARA hacia la IZQUIERDA
void Enemy::CreateEnemy5(int x, int y){
                
    this->speed = 0.0f;
    this->damage = 10;
    this->health = 20;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("hongo_sprite", "resources/hongo.png");
    this->texture = motor->getTexture("hongo_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=1;

    this->sprite_map.insert(std::pair<int,int>(0,3));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,7));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=48;
    this->alto=48;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));

    this->sprite->setPosition(x, y);
    this->col.setPosition(x+24,y);
    this->col.setSize(sf::Vector2f(24, 36));
    this->col.setFillColor(sf::Color::Blue);
    this->col2.setPosition(x-80+24,y);
    this->col2.setSize(sf::Vector2f(80, 36));
    this->col2.setFillColor(sf::Color::Green);
    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy5(float deltaTime){

    velocity.y +=981.0f*deltaTime;
    this->updateBox();
    this->updateBoxVision();

    GameState *game = GameState::Instance();

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

            velocity.y = 0;

        }


        if(this->rightColPro < game->jugador->leftCol || this->leftColPro > game->jugador->rightCol ||
        this->topColPro > game->jugador->bottomCol || this->bottomColPro < game->jugador->topCol){

            this->col2.setFillColor(sf::Color::Green);

        } else{

            this->col2.setFillColor(sf::Color::Red);

            //AQUI HAY QUE TIRAR UN PROYECTIL
//Disparar
            sf::Vector2f posEnemy = sf::Vector2f(posx, posy);
            if(relojDisparo.getElapsedTime().asSeconds() >= 1.5){
                relojDisparo.restart();
                Proyectil *proyectil= new Proyectil(2, posEnemy, true, "izquierda", 2);
                proyectilesLanzados.push_back(proyectil);

            }
            

        }
        //Posicion de los proyectiles
            if(relojProyectil.getElapsedTime().asMilliseconds() >= 20){
               relojProyectil.restart();
                for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
                    proyectilesLanzados[i]->UpdatePos(deltaTime);
                    if(proyectilesLanzados[i]->getColision()){
                        proyectilesLanzados.erase(proyectilesLanzados.begin() + i);
                    }
                }
            }

        faceRight=false;

    row=0;
    this->Animation(deltaTime, false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se MUEVE en HORIZONTAL entre 2 PUNTOS en el AIRE y DISPARA hacia ABAJO
void Enemy::CreateEnemy6(int x, int y){
                
    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo_sprite", "resources/ojo3.png");
    this->texture = motor->getTexture("ojo_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=0;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+13,y+5);
    this->col.setSize(sf::Vector2f(20, 28));
    this->col.setFillColor(sf::Color::Blue);
    this->col2.setPosition(x+13,y+5);
    this->col2.setSize(sf::Vector2f(20, 200));
    this->col2.setFillColor(sf::Color::Green);
    this->velocity.x += speed*1.5;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;
    
}

void Enemy::IAenemy6(float deltaTime){

    this->updateBox();
    this->updateBoxVision();
    posx = this->sprite->getPosition().x;
    posy = this->sprite->getPosition().y;

    GameState *game = GameState::Instance();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                this->velocity.x = 0;
                this->velocity.x += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.x = 0;
                this->velocity.x -= speed*1.5;
        }

        if(this->rightColPro < game->jugador->leftCol || this->leftColPro > game->jugador->rightCol ||
        this->topColPro > game->jugador->bottomCol || this->bottomColPro < game->jugador->topCol){

            this->col2.setFillColor(sf::Color::Green);

        } else{

            this->col2.setFillColor(sf::Color::Red);

            //AQUI HAY QUE TIRAR UN PROYECTIL
            //Disparar
            sf::Vector2f posEnemy = sf::Vector2f(posx, posy);
            if(relojDisparo.getElapsedTime().asSeconds() >= 1.5){
                relojDisparo.restart();
                Proyectil *proyectil= new Proyectil(2, posEnemy, false, "abajo",2);
                proyectilesLanzados.push_back(proyectil);
            }
            

        }
        //Posicion de los proyectiles
            if(relojProyectil.getElapsedTime().asMilliseconds() >= 20){
               relojProyectil.restart();
                for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
                    proyectilesLanzados[i]->UpdatePos(deltaTime);
                    if(proyectilesLanzados[i]->getColision()){
                        proyectilesLanzados.erase(proyectilesLanzados.begin() + i);
                    }
                }
            }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime, false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se MUEVE realizando un CUADRADO entre 4 PUNTOS en el AIRE
//orden del movimiento -> DERECHA - ARRIBA - IZQUIERDA - ABAJO
void Enemy::CreateEnemy7(int x, int y){

    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo_sprite", "resources/ojo.png");
    this->texture = motor->getTexture("ojo_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=0;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+13,y+5);
    this->col.setSize(sf::Vector2f(20, 28));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.x += speed*1.5;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy7(float deltaTime){

    this->updateBox();




    GameState *game = GameState::Instance();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.x>0){

                    this->velocity.x = 0;
                    this->velocity.y -= speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){

                if(this->velocity.y<0){

                    this->velocity.y = 0;
                    this->velocity.x -= speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                if(this->velocity.x<0){

                    this->velocity.x = 0;
                    this->velocity.y += speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.y>0){

                    this->velocity.y = 0;
                    this->velocity.x += speed*1.5;
                }
        }
    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se MUEVE realizando un CUADRADO entre 4 PUNTOS en el AIRE
//orden del movimiento -> IZQUIERDA - ARRIBA - DERECHA - ABAJO
void Enemy::CreateEnemy8(int x, int y){

    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo_sprite", "resources/ojo.png");
    this->texture = motor->getTexture("ojo_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=0;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+13,y+5);
    this->col.setSize(sf::Vector2f(20, 28));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.x -= speed*1.5;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy8(float deltaTime){

    this->updateBox();

    GameState *game = GameState::Instance();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                if(this->velocity.x<0){

                    this->velocity.x = 0;
                    this->velocity.y -= speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){

                if(this->velocity.y<0){

                    this->velocity.y = 0;
                    this->velocity.x += speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.x>0){

                    this->velocity.x = 0;
                    this->velocity.y += speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.y>0){

                    this->velocity.y = 0;
                    this->velocity.x -= speed*1.5;
                }
        }
    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

//enemigo que se MUEVE en HORIZONTAL entre 2 PUNTOS en el SUELO pero si entras en su campo de VISION se GIRA hacia ti
void Enemy::CreateEnemy9(int x, int y){

    this->speed = 50.0f;
    this->damage = 10;
    this->health = 10;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("goblin_sprite", "resources/goblin2.png");
    this->texture = motor->getTexture("goblin_sprite");
    this->sprite = new sf::Sprite(texture);
    this->row=1;

    this->sprite_map.insert(std::pair<int,int>(0,3));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 48, 32, 48));
    this->ancho=32;
    this->alto=48;
    this->sprite->setPosition(x, y);
    this->col.setPosition(x+8,y);
    this->col.setSize(sf::Vector2f(20, 36));
    this->col.setFillColor(sf::Color::Blue);
    this->col2.setPosition(x+20,y);
    this->col2.setSize(sf::Vector2f(60, 36));
    this->col2.setFillColor(sf::Color::Green);
    this->col3.setPosition(x-40,y);
    this->col3.setSize(sf::Vector2f(60, 36));
    this->col3.setFillColor(sf::Color::Green);
    this->velocity.x += speed*1.5;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IAenemy9(float deltaTime){

    velocity.y +=981.0f*deltaTime;
    this->updateBox();
    this->updateBoxVision();
    this->updateBoxVision2();

    GameState *game = GameState::Instance();

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

            velocity.y = 0;

        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                this->velocity.x = 0;
                this->velocity.x += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.x = 0;
                this->velocity.x -= speed*1.5;
        }

        if(this->rightColPro < game->jugador->leftCol || this->leftColPro > game->jugador->rightCol ||
        this->topColPro > game->jugador->bottomCol || this->bottomColPro < game->jugador->topCol){


            this->col2.setFillColor(sf::Color::Green);

        } else{

            if(this->velocity.x<0){

                this->velocity.x = 0;
                this->velocity.x += speed*1.5;
            }

            this->col2.setFillColor(sf::Color::Red);
        }

        if(this->rightColPro2 < game->jugador->leftCol || this->leftColPro2 > game->jugador->rightCol ||
        this->topColPro2 > game->jugador->bottomCol || this->bottomColPro2 < game->jugador->topCol){

            this->col3.setFillColor(sf::Color::Green);

        } else{

            if(this->velocity.x>0){

                this->velocity.x = 0;
                this->velocity.x -= speed*1.5;
            }

            this->col3.setFillColor(sf::Color::Red);

        }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col3.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

}

void Enemy::hit(int power, int frozen){
    GameState *game = GameState::Instance();
    row=4;
    srand(time(NULL));
    this->Animation(this->deltaTime,true);
    health = health-power;
    updateVidaEnemigos(health);
    if(health<=0){
        std::map<int, Enemy*> enemylist_ac;
        int i=0;
        for(int j=0; j<(int)game->zonactual->enemylist.size(); j++){
            if(game->zonactual->enemylist[j]==this){
                if(game->zonactual->enemylist[j]->tipo == 1){
                    game->jugador->money = game->jugador->money + (rand() % (6-1));
                }else{
                    game->jugador->money = game->jugador->money + (rand() % (11-1));
                }
                delete game->zonactual->enemylist[j];
                game->zonactual->totalenemylvl--;
                
            }else{
                enemylist_ac[i] = game->zonactual->enemylist[j];
                i++;
            }
        }
        game->zonactual->enemylist=enemylist_ac;

        if(this->tipo==10){

            game->jugador->saltoEscalada = true;
        }

        if(this->tipo==11){

            game->jugador->dash = true;
        }
    }
}

void Enemy::Animation(float deltaTime, bool dolor){
    if(relojAnimacion->getElapsedTime().asSeconds() >= 0.15 || dolor){
        relojAnimacion->restart();
        if((int) currentImage.y != row){
            currentImage.x = 0;
        }
        if((int) currentImage.y==4){
            relojDuele->restart();
        }

        currentImage.y = row;
        totalTime += deltaTime;


        //control para cambiar de sprite respecto al switch time
        if(totalTime >= switchTime)
        {   
                totalTime -= switchTime;
                currentImage.x++;

                if((int)currentImage.x > sprite_map[currentImage.y])
                {  
                    currentImage.x = 0;
                }
        }
        int top = currentImage.y * alto;

        //controlamos la orientacion del sprite
        
        int left;
        int width;
        
        if(faceRight)
        {
            left = currentImage.x * ancho;
            width = ancho;
        }

        else
        {
            left = (currentImage.x +1) * ancho;
            width = -ancho;
        }


        sprite->setTextureRect(sf::IntRect(left, top, width, alto));
    }
    
}

void Enemy::CreateBoss1(int x, int y){

    this->speed = 50.0f;
    this->damage = 20;
    this->health = 200;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo2_sprite", "resources/ojo2.png");

    this->texture = motor->getTexture("ojo2_sprite");
    this->sprite = new sf::Sprite(texture);
    this->sprite->setScale(2,2);
    this->row=0;
    this->relojTeleport = new sf::Clock;
    this->relojChange = new sf::Clock;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=48;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);

    this->col.setPosition(x+25,y+10);
    this->col.setSize(sf::Vector2f(50, 50));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.y += speed*1.5;

    //cajas de colision para el patron de ataque

    this->colB1.setPosition(x+(50/2),y+(50/2)-40);
    this->colB1.setSize(sf::Vector2f(25,25));
    this->colB1.setFillColor(sf::Color::Green);

    this->colB2.setPosition(x+(50/2)+40,y+(50/2));
    this->colB2.setSize(sf::Vector2f(25,25));
    this->colB2.setFillColor(sf::Color::Green);

    this->colB3.setPosition(x+(50/2),y+(50/2)+40);
    this->colB3.setSize(sf::Vector2f(25,25));
    this->colB3.setFillColor(sf::Color::Green);

    this->colB4.setPosition(x+(50/2)-40,y+(50/2));
    this->colB4.setSize(sf::Vector2f(25,25));
    this->colB4.setFillColor(sf::Color::Green);
    
    /*motor->addTexture("Proyectiles2", "resources/sprite_sheet.png");
    this->textureB = motor->getTexture("Proyectiles2");
    
    this->spriteB1 = new sf::Sprite(textureB);
    this->spriteB1->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB1->setPosition(x+(50/2),y+(50/2)-40);

    this->spriteB2 = new sf::Sprite(textureB);
    this->spriteB2->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB2->setPosition(x+(50/2)+40,y+(50/2));

    this->spriteB3 = new sf::Sprite(textureB);
    this->spriteB3->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB3->setPosition(x+(50/2),y+(50/2)+40);

    this->spriteB4 = new sf::Sprite(textureB);
    this->spriteB4->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB4->setPosition(x+(50/2)-40,y+(50/2));*/

    idPatron = 1;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IABoss1(float deltaTime){

    this->updateBox();
    this->updateBoxOrbitales();

    posx = this->sprite->getPosition().x;
    posy = this->sprite->getPosition().y;

    GameState *game = GameState::Instance();
    srand(time(NULL));

    if(this->relojTeleport->getElapsedTime().asSeconds() >= 4){
        this->relojTeleport->restart();
        int num = rand()%(6-1);

        switch(num){

            case 1:
                this->sprite->setPosition(352.0f, 380.0f);
                this->col.setPosition(352.0f+25.0f, 380.0f+10.0f);
                
                break;
            case 2:
                this->sprite->setPosition(99.0f, 342.0f);
                this->col.setPosition(99.0f+25.0f,342.0f+10.0f);
                //setPositionVidaEnemigos(this->posx, this->posy);
                break;
            case 3:
                this->sprite->setPosition(99.0f, 197.0f);
                this->col.setPosition(99.0f+25.0f, 197.0f+10.0f);
                //setPositionVidaEnemigos(this->posx, this->posy);
                break;
            case 4:
                this->sprite->setPosition(588.0f, 342.0f);
                this->col.setPosition(588.0f+25.0f, 342.0f+10.0f);
                //setPositionVidaEnemigos(this->posx, this->posy);
                break;
            case 5:
                this->sprite->setPosition(588.0f, 211.0f);
                this->col.setPosition(588.0f+25.0f, 211.0f+10.0f);
                //setPositionVidaEnemigos(this->posx, this->posy);
                break;
        }
    }

        if(this->relojChange->getElapsedTime().asSeconds() >= 2){
            this->relojChange->restart();

            if(idPatron==1){

                this->colB1.setPosition(posx+(50/2),posy+(50/2)-60);
                //this->spriteB1->setPosition(posx+(50/2),posy+(50/2)-60);

                this->colB2.setPosition(posx+(50/2)+60,posy+(50/2));
                //this->spriteB2->setPosition(posx+(50/2)+40,posy+(50/2));

                this->colB3.setPosition(posx+(50/2),posy+(50/2)+60);
                //this->spriteB3->setPosition(posx+(50/2),posy+(50/2)+60);

                this->colB4.setPosition(posx+(50/2)-60,posy+(50/2));
                //this->spriteB4->setPosition(posx+(50/2)-60,posy+(50/2));

                idPatron = 2;

            } else if(idPatron==2){

                this->colB1.setPosition(posx+(50/2)+40,posy+(50/2)-40);
                //this->spriteB1->setPosition(posx+(50/2)+40,posy+(50/2)-40);

                this->colB2.setPosition(posx+(50/2)+40,posy+(50/2)+40);
                //this->spriteB2->setPosition(posx+(50/2)+40,posy+(50/2)+40);

                this->colB3.setPosition(posx+(50/2)-40,posy+(50/2)+40);
                //this->spriteB3->setPosition(posx+(50/2)-40,posy+(50/2)+40);

                this->colB4.setPosition(posx+(50/2)-40,posy+(50/2)-40);
                //this->spriteB4->setPosition(posx+(50/2)-40,posy+(50/2)-40);

                idPatron = 3;

            } else if(idPatron==3){

                this->colB1.setPosition(posx+(50/2)+60,posy+(50/2)-60);
                //this->spriteB1->setPosition(posx+(50/2)+60,posy+(50/2)-60);

                this->colB2.setPosition(posx+(50/2)+60,posy+(50/2)+60);
                //this->spriteB2->setPosition(posx+(50/2)+60,posy+(50/2)+60);

                this->colB3.setPosition(posx+(50/2)-60,posy+(50/2)+60);
                //this->spriteB3->setPosition(posx+(50/2)-60,posy+(50/2)+60);

                this->colB4.setPosition(posx+(50/2)-60,posy+(50/2)-60);
                //this->spriteB4->setPosition(posx+(50/2)-60,posy+(50/2)-60);

                idPatron = 1;

            }
        }


        orbitalesPlayerCollisions();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){

                this->velocity.y = 0;
                this->velocity.y += speed*1.5;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                this->velocity.y = 0;
                this->velocity.y -= speed*1.5;
        }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB1.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB1->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB2->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB3.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB3->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB4.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB4->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    
    setPositionVidaEnemigos(this->posx, this->posy);
}

void Enemy::vidaEnemigos(int posX, int posY, int vida){
    float maxptosVidaPixel = 50.f;
    marcoVida = sf::RectangleShape(sf::Vector2f(maxptosVidaPixel,5.f));
    marcoVida.setFillColor(sf::Color::Transparent);
    marcoVida.setOutlineThickness(0.8);
    marcoVida.setOutlineColor(sf::Color::Red);
    marcoVida.setOrigin(0,0);
    marcoVida.setPosition(posX,posY - 15.f);

    marcoVida.scale(0.75,0.75);


    vidaActual = sf::RectangleShape(sf::Vector2f(maxptosVidaPixel,5.f));
    vidaActual.setFillColor(sf::Color::Red);
    vidaActual.setOrigin(0,0);
    vidaActual.setPosition(posX,posY - 15.f);

    vidaActual.scale(0.75,0.75);

    labelVida = sf::Text();
    labelVida.setFont(motor->getFont("Dungeon"));
    labelVida.setCharacterSize(12);
    labelVida.setStyle(sf::Text::Bold);
    labelVida.setColor(sf::Color::White);
    labelVida.setPosition(vidaActual.getPosition().x + 15.f, vidaActual.getPosition().y - 5.f);
    std::string n;
    std::ostringstream np;
    np << vida;
    n = np.str();
    labelVida.setString(n);
}

void Enemy::updateVidaEnemigos(int vida){
    float ptosVida = 0.0f;

    if(vida > 0){
        ptosVida = (vida * 50)/vidaT;       
    }
    vidaActual.setSize(sf::Vector2f(ptosVida,5.f));

   
    std::string n;
    std::ostringstream np;
    np << vida;
    n = np.str();
    labelVida.setString(n);
   

}

void Enemy::moveVidaEnemigos(float x, float y){
    marcoVida.move(x,y);
    vidaActual.move(x,y);
    labelVida.move(x,y);
}


void Enemy::setPositionVidaEnemigos(float x, float y){
    marcoVida.setPosition(x,y);
    vidaActual.setPosition(x,y);
    labelVida.setPosition(x,y);
}

void Enemy::updateBoxOrbitales(){

    bottomColB1 = colB1.getPosition().y + colB1.getSize().y;
    leftColB1 = colB1.getPosition().x;
    rightColB1 = colB1.getPosition().x + colB1.getSize().x;
    topColB1 = colB1.getPosition().y;

    bottomColB2 = colB2.getPosition().y + colB2.getSize().y;
    leftColB2 = colB2.getPosition().x;
    rightColB2 = colB2.getPosition().x + colB2.getSize().x;
    topColB2 = colB2.getPosition().y;

    bottomColB3 = colB3.getPosition().y + colB3.getSize().y;
    leftColB3 = colB3.getPosition().x;
    rightColB3 = colB3.getPosition().x + colB3.getSize().x;
    topColB3 = colB3.getPosition().y;

    bottomColB4 = colB4.getPosition().y + colB4.getSize().y;
    leftColB4 = colB4.getPosition().x;
    rightColB4 = colB4.getPosition().x + colB4.getSize().x;
    topColB4 = colB4.getPosition().y;
    
}

void Enemy::orbitalesPlayerCollisions(){

    GameState *game = GameState::Instance();

        if(this->rightColB1 < game->jugador->leftCol || this->leftColB1 > game->jugador->rightCol ||
        this->topColB1 > game->jugador->bottomCol || this->bottomColB1 < game->jugador->topCol){
        
        } else {
            game->jugador->proyectilCollision();
        }

        if(this->rightColB2 < game->jugador->leftCol || this->leftColB2 > game->jugador->rightCol ||
        this->topColB2 > game->jugador->bottomCol || this->bottomColB2 < game->jugador->topCol){
        
        } else {
            game->jugador->proyectilCollision();
        }
        
        if(this->rightColB3 < game->jugador->leftCol || this->leftColB3 > game->jugador->rightCol ||
        this->topColB3 > game->jugador->bottomCol || this->bottomColB3 < game->jugador->topCol){
        
        } else {
            game->jugador->proyectilCollision();
        }

        if(this->rightColB4 < game->jugador->leftCol || this->leftColB4 > game->jugador->rightCol ||
        this->topColB4 > game->jugador->bottomCol || this->bottomColB4 < game->jugador->topCol){
        
        } else {
            game->jugador->proyectilCollision();
        }
}

void Enemy::CreateBoss2(int x, int y){

    this->speed = 50.0f;
    this->damage = 20;
    this->health = 200;
    this->motor = Motor2D::Instance();
    this->motor->addTexture("ojo2_sprite", "resources/ojo2.png");
    this->texture = motor->getTexture("ojo2_sprite");
    this->sprite = new sf::Sprite(texture);
    this->sprite->setScale(2,2);
    this->row=0;
    this->relojTeleport = new sf::Clock;
    this->relojChange = new sf::Clock;

    this->sprite_map.insert(std::pair<int,int>(0,6));
    this->sprite_map.insert(std::pair<int,int>(1,7));
    this->sprite_map.insert(std::pair<int,int>(2,5));
    this->sprite_map.insert(std::pair<int,int>(3,3));
    this->sprite_map.insert(std::pair<int,int>(4,1));

    this->ancho=47;
    this->alto=32;
    this->sprite->setTextureRect(sf::IntRect(0 * ancho, 0 * alto, ancho, alto));
    this->sprite->setPosition(x, y);

    this->col.setPosition(x+25,y+10);
    this->col.setSize(sf::Vector2f(50, 50));
    this->col.setFillColor(sf::Color::Blue);
    this->velocity.y += speed*1.5;

    //cajas de colision para el patron de ataque

    this->colB1.setPosition(x+(50/2),y+(50/2)-40);
    this->colB1.setSize(sf::Vector2f(25,25));
    this->colB1.setFillColor(sf::Color::Green);

    this->colB2.setPosition(x+(50/2)+40,y+(50/2));
    this->colB2.setSize(sf::Vector2f(25,25));
    this->colB2.setFillColor(sf::Color::Green);

    this->colB3.setPosition(x+(50/2),y+(50/2)+40);
    this->colB3.setSize(sf::Vector2f(25,25));
    this->colB3.setFillColor(sf::Color::Green);

    this->colB4.setPosition(x+(50/2)-40,y+(50/2));
    this->colB4.setSize(sf::Vector2f(25,25));
    this->colB4.setFillColor(sf::Color::Green);
    
    /*motor->addTexture("Proyectiles2", "resources/sprite_sheet.png");
    this->textureB = motor->getTexture("Proyectiles2");
    
    this->spriteB1 = new sf::Sprite(textureB);
    this->spriteB1->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB1->setPosition(x+(50/2),y+(50/2)-40);

    this->spriteB2 = new sf::Sprite(textureB);
    this->spriteB2->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB2->setPosition(x+(50/2)+40,y+(50/2));

    this->spriteB3 = new sf::Sprite(textureB);
    this->spriteB3->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB3->setPosition(x+(50/2),y+(50/2)+40);

    this->spriteB4 = new sf::Sprite(textureB);
    this->spriteB4->setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    this->spriteB4->setPosition(x+(50/2)-40,y+(50/2));*/

    idPatron = 1;

    vidaEnemigos(this->posx, this->posy, this->health);
    vidaT = this->health;

}

void Enemy::IABoss2(float deltaTime){

    this->updateBox();
    this->updateBoxOrbitales();

    posx = this->sprite->getPosition().x;
    posy = this->sprite->getPosition().y;

    GameState *game = GameState::Instance();
    srand(time(NULL));

    /*if(this->relojTeleport->getElapsedTime().asSeconds() >= 4){
        this->relojTeleport->restart();
        int num = rand()%(6-1);

        switch(num){

            case 1:
                this->sprite->setPosition(352.0f, 380.0f);
                this->col.setPosition(352.0f, 380.0f);
                break;
            case 2:
                this->sprite->setPosition(99.0f, 342.0f);
                this->col.setPosition(99.0f,342.0f);
                break;
            case 3:
                this->sprite->setPosition(99.0f, 197.0f);
                this->col.setPosition(99.0f, 197.0f);
                break;
            case 4:
                this->sprite->setPosition(588.0f, 342.0f);
                this->col.setPosition(588.0f, 342.0f);
                break;
            case 5:
                this->sprite->setPosition(588.0f, 211.0f);
                this->col.setPosition(588.0f, 211.0f);
                break;
        }
    }*/

        if(this->relojChange->getElapsedTime().asSeconds() >= 2){
            this->relojChange->restart();

            if(idPatron==1){

                this->colB1.setPosition(posx+(50/2),posy+(50/2)-60);
                //this->spriteB1->setPosition(posx+(50/2),posy+(50/2)-60);

                this->colB2.setPosition(posx+(50/2)+60,posy+(50/2));
                //this->spriteB2->setPosition(posx+(50/2)+40,posy+(50/2));

                this->colB3.setPosition(posx+(50/2),posy+(50/2)+60);
                //this->spriteB3->setPosition(posx+(50/2),posy+(50/2)+60);

                this->colB4.setPosition(posx+(50/2)-60,posy+(50/2));
                //this->spriteB4->setPosition(posx+(50/2)-60,posy+(50/2));

                idPatron = 2;

            } else if(idPatron==2){

                this->colB1.setPosition(posx+(50/2)+40,posy+(50/2)-40);
                //this->spriteB1->setPosition(posx+(50/2)+40,posy+(50/2)-40);

                this->colB2.setPosition(posx+(50/2)+40,posy+(50/2)+40);
                //this->spriteB2->setPosition(posx+(50/2)+40,posy+(50/2)+40);

                this->colB3.setPosition(posx+(50/2)-40,posy+(50/2)+40);
                //this->spriteB3->setPosition(posx+(50/2)-40,posy+(50/2)+40);

                this->colB4.setPosition(posx+(50/2)-40,posy+(50/2)-40);
                //this->spriteB4->setPosition(posx+(50/2)-40,posy+(50/2)-40);

                idPatron = 3;

            } else if(idPatron==3){

                this->colB1.setPosition(posx+(50/2)+60,posy+(50/2)-60);
                //this->spriteB1->setPosition(posx+(50/2)+60,posy+(50/2)-60);

                this->colB2.setPosition(posx+(50/2)+60,posy+(50/2)+60);
                //this->spriteB2->setPosition(posx+(50/2)+60,posy+(50/2)+60);

                this->colB3.setPosition(posx+(50/2)-60,posy+(50/2)+60);
                //this->spriteB3->setPosition(posx+(50/2)-60,posy+(50/2)+60);

                this->colB4.setPosition(posx+(50/2)-60,posy+(50/2)-60);
                //this->spriteB4->setPosition(posx+(50/2)-60,posy+(50/2)-60);

                idPatron = 1;

            }
        }


        orbitalesPlayerCollisions();


        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.x>0){

                    this->velocity.x = 0;
                    this->velocity.y -= speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){

                if(this->velocity.y<0){

                    this->velocity.y = 0;
                    this->velocity.x -= speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0){

                if(this->velocity.x<0){

                    this->velocity.x = 0;
                    this->velocity.y += speed*1.5;
                }
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 && 
            game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){

                if(this->velocity.y>0){

                    this->velocity.y = 0;
                    this->velocity.x += speed*1.5;
                }
        }

    if(velocity.x>0){
        faceRight=true;
    }
    if(velocity.x<0){
        faceRight=false;
    }
    row=1;
    this->Animation(deltaTime,false);
    this->sprite->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->col.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB1.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB1->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB2.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB2->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB3.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB3->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    this->colB4.move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    //this->spriteB4->move(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));
    moveVidaEnemigos(std::floor(velocity.x*deltaTime),std::floor(velocity.y*deltaTime));

    setPositionVidaEnemigos(this->posx, this->posy);
}
