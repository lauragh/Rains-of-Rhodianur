#include "../motor2D/proyectil.h"
#include "../states/game_state.h"


Proyectil::Proyectil(int tipo_proyectil, sf::Vector2f pos, bool face, std::string dir, int quien){
    motor = Motor2D::Instance();
    motor->addTexture("Proyectiles", "resources/sprite_sheet.png");

    texture = motor->getTexture("Proyectiles");
    sprite.setTexture(texture);
    //sprite.setOrigin(32 / 2, 32 / 2);

    faceRight = face;
    colision = false;
    direccion = dir;
    tirador = quien;

    if(faceRight){
        if(quien == 2){
            posicionInicial.x = pos.x+35;
            posicionInicial.y = pos.y+15;
            posicion.x = pos.x+35;
            posicion.y = pos.y+15;
        }else{
            posicionInicial.x = pos.x+35;
            posicionInicial.y = pos.y;
            posicion.x = pos.x+35;
            posicion.y = pos.y;
        }
    }else{
        if(quien == 2){
            posicionInicial.x = pos.x+15;
            posicionInicial.y = pos.y+15;
            posicion.x = pos.x+15;
            posicion.y = pos.y+15;
        }else{
            posicionInicial.x = pos.x+15;
            posicionInicial.y = pos.y;
            posicion.x = pos.x+15;
            posicion.y = pos.y;
        }        
    }

    sprite.setPosition(posicionInicial.x, posicionInicial.y);

    if ((tipo_proyectil == 1||tipo_proyectil == 8||tipo_proyectil == 9) && faceRight){//Flecha
        sprite.setTextureRect(sf::IntRect(1*32, 2*32, 32, 32));
        col.setSize(sf::Vector2f(24, 12));
    }else if ((tipo_proyectil == 1||tipo_proyectil == 8||tipo_proyectil == 9) && !faceRight){ //Flecha invertida
        sprite.setTextureRect(sf::IntRect((1+1)*32, 2*32, -1*32, 32));
    }else if (tipo_proyectil == 2){ //Fuego
        sprite.setTextureRect(sf::IntRect(6*32, 0*32, 32, 32));
    }else if (tipo_proyectil == 3){ //Fuego Alfa
        sprite.setTextureRect(sf::IntRect(7*32, 0*32, 32, 32));
    }else if (tipo_proyectil == 4){ //Fuego Omega
        sprite.setTextureRect(sf::IntRect(8*32, 0*32, 32, 32));
    }else if (tipo_proyectil == 5){ //Fuego
        sprite.setTextureRect(sf::IntRect(9*32, 0*32, 32, 32));
    }else if (tipo_proyectil == 6){ //Fuego
        sprite.setTextureRect(sf::IntRect(10*32, 0*32, 32, 32));
    }else if (tipo_proyectil == 7){ //Fuego
        sprite.setTextureRect(sf::IntRect(11*32, 0*32, 32, 32));
    }


    col.setPosition(posicionInicial.x, posicionInicial.y);
    col.setSize(sf::Vector2f(26, 16));
    col.setFillColor(sf::Color::Blue);

    tipo = tipo_proyectil;
    
}

Proyectil::~Proyectil(){
    sprite=sf::Sprite();
    texture=sf::Texture();
    posicion=sf::Vector2f();
    posicionInicial=sf::Vector2f();
    tipo=0;
    faceRight=false;
    direccion="";
    //colisiones
    col=sf::RectangleShape();
    tirador=0;

    bottomCol=0;
    leftCol=0;
    rightCol=0;
    topCol=0;

    cornerTiles.clear();
    colision=false;

    motor=NULL;
}

int Proyectil::getTipo(){
    return tipo;
}

void Proyectil::setPosicion(sf::Vector2f posi){
    posicion = posi;
    sprite.setPosition(posicion.x, posicion.y-7);
}


void Proyectil::Draw(){

    if(motor->debug){
        motor->drawRectangleShape(col);
    }
    motor->drawSprite(sprite);
}

void Proyectil::UpdatePos(float delta){
    float newX,newY;
    delta = delta * 1;
    
    if(direccion == "derecha"){
        newX = posicion.x + (posicionInicial.x * delta);
        sf::Vector2f derecha(newX, posicion.y);
        setPosicion(derecha);
        col.setPosition(newX, posicion.y);
    }else if(direccion == "izquierda")  {
        newX = posicion.x - (posicionInicial.x * delta);
        sf::Vector2f izquierda(newX, posicion.y);
        setPosicion(izquierda);
        col.setPosition(newX, posicion.y);
    }else if(direccion == "arriba")  {
        newY = posicion.y - (posicionInicial.y * delta);
        sf::Vector2f arriba(posicion.x, newY);
        setPosicion(arriba);
        col.setPosition(posicion.x, newY);
    }else if(direccion == "abajo")  {
        newY = posicion.y + (posicionInicial.y * delta);
        sf::Vector2f abajo(posicion.x, newY);
        setPosicion(abajo);
        col.setPosition(posicion.x, newY);
    } 

    this->updateBox();

    int res_col=this->collisions();


    if (res_col==0){
        col.setFillColor(sf::Color::Blue);
    } else if(res_col==1||res_col==2){
        col.setFillColor(sf::Color::Red);
    } 
    
}

void Proyectil::updateBox(){

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

int Proyectil::collisions(){

    bool golpea=false;
    GameState *game = GameState::Instance();

    if(tirador==1){

    for(int j=0; j<(int)game->zonactual->enemylist.size(); j++){

        if(this->rightCol < game->zonactual->enemylist[j]->leftCol || this->leftCol > game->zonactual->enemylist[j]->rightCol ||
        this->topCol > game->zonactual->enemylist[j]->bottomCol || this->bottomCol < game->zonactual->enemylist[j]->topCol){

            game->zonactual->enemylist[j]->collisions(false);

        } else{
                    game->zonactual->enemylist[j]->collisions(true);
                    colision = true;

                    if (tipo == 1){ //Flecha
                        game->zonactual->enemylist[j]->hit(5,0);
                    }else if (tipo == 2){ //Fuego
                        game->zonactual->enemylist[j]->hit(7,0);
                    }else if (tipo == 3){ //Fuego Alfa
                        game->zonactual->enemylist[j]->hit(12,0);
                    }else if (tipo == 4){ //Fuego Omega
                        game->zonactual->enemylist[j]->hit(30,0);
                    }else if (tipo == 5){ //Hielo
                        game->zonactual->enemylist[j]->hit(6,1);
                    }else if (tipo == 6){ //Hielo Alfa
                        game->zonactual->enemylist[j]->hit(6,2);
                    }else if (tipo == 7){ //Hielo Omega
                        game->zonactual->enemylist[j]->hit(20,3);
                    }else if (tipo == 8){ //Flecha rota
                        game->zonactual->enemylist[j]->hit(15,0);
                    }else if (tipo == 9){ //Flecha mas rota
                        game->zonactual->enemylist[j]->hit(10,0);
                    }
                    golpea=true;
                    game->zonactual->enemylist[j]->collisions(true);
                    colision = true;

                    return 2;
            
        }
    }
} else if(tirador == 2){

        if(this->rightCol < game->jugador->leftCol || this->leftCol > game->jugador->rightCol ||
        this->topCol > game->jugador->bottomCol || this->bottomCol < game->jugador->topCol){


        } else{

            game->jugador->proyectilCollision();
        }

}

    //colision con el mapa
    if(!golpea){

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[2].y][this->cornerTiles[2].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[3].y][this->cornerTiles[3].x]!=0){
            colision = true;
            return 1;
        }

        if(game->zonactual->mapactual->gitMatrix[this->cornerTiles[0].y][this->cornerTiles[0].x]!=0 || 
        game->zonactual->mapactual->gitMatrix[this->cornerTiles[1].y][this->cornerTiles[1].x]!=0){
            colision = true;
            return 2;
        }
        
        colision = false;
        return 0;
    }
}