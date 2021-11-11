#include "interfaz.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cmath>

#include "../states/game_state.h"
//constructor
Interfaz::Interfaz(){

}

Interfaz::~Interfaz(){
    pocionVida=sf::Sprite();
    pocionMana=sf::Sprite();
    armaP=sf::Sprite();
    armaS=sf::Sprite();
    dinero=sf::Sprite();
    flechas=sf::Sprite();
    texture=sf::Texture();
    view=sf::View();
    marco=sf::RectangleShape();
    marco2=sf::RectangleShape();
    vidaTotal=sf::RectangleShape();
    manaTotal=sf::RectangleShape();
    vida=sf::RectangleShape();
    mana=sf::RectangleShape();
    label=sf::Text();
    label2=sf::Text();
    label3=sf::Text();
    fuente=sf::Font();
    numVidas=sf::Text();
    numMana=sf::Text();
    cantMonedas=sf::Text();
    numFlechas=sf::Text();
    ptosVida=0;
    ptosMana=0;
    ptosArmadura=0;
    vidaT=0;
    manaT=0;
    maxptosVidaPixel=0;
    maxManaPixel=0;
    numPotiVida=0;
    numPotiMana=0;
    cantDinero=0;
    cantFlechas=0;
    ataqueSecundarioSelected=std::string();

    motor=NULL;
}

Interfaz::Interfaz(sf::Vector2f position,float puntosVida, float puntosTotalV, float puntosMana, float puntosTotalM, int cantDinero, int numPotiVida, int numPotiMana, int cantFlechas, std::vector <Object*> equipado, std::string ataqueSecundarioSelected) {

    motor = Motor2D::Instance();

    motor->addTexture("sprite_sheet", "resources/sprite_sheet.png");

    texture = motor->getTexture("sprite_sheet");
    
    motor->addFont("Dungeon", "resources/dungeon.TTF");

    fuente = motor->getFont("Dungeon");
   
    this->numPotiVida = numPotiVida;
    this->numPotiMana = numPotiMana;
    this->cantDinero = cantDinero;
    this->cantFlechas = cantFlechas;
    this->ataqueSecundarioSelected=ataqueSecundarioSelected;

    createView(position.x, position.y);    

    createBarras();
    createArmaP(-1,-1);
    createArmaS(-1,-1);
    createPociones();
    createDinero();
  

    float puntosArmadura = 0;

    if(equipado.size() != 0){
        for( unsigned int i = 0; i < equipado.size(); i++){
            if(equipado[i]->getType() == "Proyectil"&& equipado[i]->getName()==ataqueSecundarioSelected){
                createArmaS(equipado[i]->getColumna(),equipado[i]->getFila());
                createFlechas();
            }

            if(equipado[i]->getType() == "Principal"){
                createArmaP(equipado[i]->getColumna(),equipado[i]->getFila());
            }

            if(equipado[i]->getType() == "Magia"&& equipado[i]->getName()==ataqueSecundarioSelected){   
                createArmaS(equipado[i]->getColumna(),equipado[i]->getFila());
            }
          
        }

        vidaT = puntosTotalV;
        manaT = puntosTotalM;
        ptosVida = puntosVida;
        ptosMana = puntosMana;
    }
}

//anadir en el update de la vida, el mana, etc
void Interfaz::update(float posX, float posY, sf::Vector2f velocity, float deltaTime, float puntosVida, float puntosTotalV, float puntosMana, float puntosTotalM, int cantDinero, int numPotiVida, int numPotiMana, int cantFlechas, std::vector <Object*> equipado, std::string ataqueSecundarioSelected){

    GameState *estadoJuego = GameState::Instance();
    int zonaMapa = estadoJuego->zonactual->idMapa;
    float posicionY;
    this->ataqueSecundarioSelected=ataqueSecundarioSelected;
        

    if(dinero.getPosition().y < 0){
         posicionY = posY + (dinero.getPosition().y*-1);
    }
    else{
        posicionY = posY - dinero.getPosition().y;
    }

    if(posicionY > 150 && posicionY < 180){
        //Aldea
        if(zonaMapa == 1){
            if(posX > 212 && posX < 214){
                setInterfaz(posX + 100.f,posY - 100.f);
            }
            else if(posX >= 214 && posX <= 304){
                moverInterfaz(0,0);
            }
            else if(posX > 304 && posX < 1609){                    
                moverInterfaz(velocity.x*deltaTime,0);
            }
            else if (posX >= 1609 && posX < 1786){
                moverInterfaz(0,0);
            }
            else if(posX >= 1786 && posX < 1787){
                setInterfaz(posX - 200.f,posY - 100.f);
            }  
        }
        //bosque
        else if(zonaMapa == 2){

            if(posX > 114 && posX < 115){
                setInterfaz(posX + 200.f,posY - 100.f);
            }
            else if(posX >= 115 && posX <= 292){
                moverInterfaz(0,0);
            }
            else if(posX > 292 && posX < 2087){                    
                moverInterfaz(velocity.x*deltaTime,0);
            }
            else if (posX >= 2087){
                moverInterfaz(0,0);
            }
             else if(posX > 99 && posY > 1180){
                setInterfaz(posX + 200.f,posY - 100.f);
            } 
        }
        //montaña
        else if(zonaMapa == 3){
             if(posX > 1396 && posX <= 1397){
                setInterfaz(posX - 230.f, posY - 100.f);
             }
             else if(posX > 1275 && posX <= 1396){
                moverInterfaz(0,0);
             }
            else if( posX > 281 && posX <= 1275){
                moverInterfaz(velocity.x*deltaTime,0);
            }
            else if(posX <= 281){
                moverInterfaz(0,0);
            }
              else if(posY > 378 && posX > 1467 && posX < 1468){
                setInterfaz(posX - 180.f, posY - 100.f);
            }
            else if(posX >= 1468){
                moverInterfaz(0,0);
            }
        }
        //boss bosque
        else if(zonaMapa == 4){
            if(posX > 101 && posX <= 110){
                setInterfaz(posX + 250.f, posY - 100.f);
             }
             else if(posX > 110 && posX <= 345){
                moverInterfaz(0,0);
             }
            else if( posX > 345 && posX < 481){
                moverInterfaz(velocity.x*deltaTime,0);
            }
            else if(posX >= 481){
                moverInterfaz(0,0);
            }
        }
        //boss montaña
          else if(zonaMapa == 5){
            if(posX > 74 && posX <= 75){
                setInterfaz(posX + 200.f, posY - 100.f);
             }
             else if(posX > 75 && posX <= 296){
                moverInterfaz(0,0);
             }
             else if(posX > 296 && posX < 455){
                moverInterfaz(velocity.x*deltaTime,0);
             }
             else if(posX >= 455){
                moverInterfaz(0,0);
             }
        }
    }
    else if(posicionY <= 150){
        //Aldea
        if(zonaMapa == 1){
           if(posX > 212 && posX < 214){
                setInterfaz(posX + 100.f,posY - 100.f);
            }
            else if(posX >= 214 && posX <= 304){
                moverInterfaz(0,0);
            }
            else if(posX > 304 && posX < 1609){                    
                moverInterfaz(velocity.x*deltaTime,-1);
            }
            else if (posX >= 1609 && posX < 1786){
                moverInterfaz(0,0);
            }
            else if(posX >= 1786 && posX < 1787){
                setInterfaz(posX -180.f,posY - 100.f);
            }   
        }
        //bosque
        else if(zonaMapa == 2){
             if(posX > 114 && posX < 115){
                setInterfaz(posX + 230.f,posY - 100.f);
            }
            else if(posX >= 115 && posX <= 292){
                moverInterfaz(0,0);
            }
            else if(posX > 292 && posX < 2087){                    
                moverInterfaz(velocity.x*deltaTime,-1);
            }
            else if (posX >= 2087){
                moverInterfaz(0,0);
            }
             else if(posX > 99 && posY > 1180){
                setInterfaz(posX + 200.f,posY - 100.f);
            } 
        }
        //montaña
        else if(zonaMapa == 3){
              if(posX > 1396 && posX <= 1397){
                setInterfaz(posX - 100.f, posY - 100.f);
             }
             else if(posX > 1275 && posX <= 1396){
                moverInterfaz(0,0);
             }
            else if( posX > 281 && posX <= 1275){
                moverInterfaz(velocity.x*deltaTime,-1);
            }
            else if(posX <= 281){
                moverInterfaz(0,-1);
            }
              else if(posY > 378 && posX > 1467 && posX < 1468){
                setInterfaz(posX - 180.f, posY - 100.f);
            }
            else if(posX >= 1468){
                moverInterfaz(0,0);
            }
        }
          //boss bosque
        else if(zonaMapa == 4){
             if(posX > 101 && posX <= 110){
                setInterfaz(posX + 250.f, posY - 100.f);
             }
             else if(posX > 110 && posX <= 345){
                moverInterfaz(0,0);
             }
            else if( posX > 345 && posX < 481){
                moverInterfaz(velocity.x*deltaTime,-1);
            }
            else if(posX >= 481){
                moverInterfaz(0,-1);
            }
        }

        //boss montaña
        else if(zonaMapa == 5){
            if(posX > 74 && posX <= 75){
                setInterfaz(posX + 200.f, posY - 100.f);
             }
             else if(posX > 75 && posX <= 296){
                moverInterfaz(0,0);
             }
             else if(posX > 296 && posX < 455){
                moverInterfaz(velocity.x*deltaTime,-1);
             }
             else if(posX >= 455){
                moverInterfaz(0,-1);
             }
        }
    }

    else if(posicionY >= 180){
        //Aldea
        if(zonaMapa == 1){
            if(posX > 212 && posX < 214){
                setInterfaz(posX + 100.f,posY - 100.f);
            }
            else if(posX >= 214 && posX <= 328){
                moverInterfaz(0,0);
            }
            else if(posX > 328 && posX < 1609){                    
                moverInterfaz(velocity.x*deltaTime,velocity.y*deltaTime);
            }
            else if (posX >= 1609 && posX < 1786){
                moverInterfaz(0,0);
            }
            else if(posX >= 1786 && posX < 1787){
                setInterfaz(posX -180.f,posY - 100.f);
            }   
        }
        
        //bosque
        else if(zonaMapa == 2){
           if(posX > 114 && posX < 115){
                setInterfaz(posX + 200.f,posY - 100.f);
            }
            else if(posX >= 115 && posX <= 292){
                moverInterfaz(0,0);
            }
            else if(posX > 292 && posX < 2087){                    
                moverInterfaz(velocity.x*deltaTime,velocity.y*deltaTime);
            }
            else if (posX >= 2087){
                moverInterfaz(0,velocity.y*deltaTime);
            }
             else if(posX > 99 && posY > 1180){
                setInterfaz(posX + 200.f,posY - 100.f);
            } 
        }
        //montaña
        else if(zonaMapa == 3){
             if(posX > 1396 && posX <= 1397){
                setInterfaz(posX - 100.f, posY - 100.f);
             }
             else if(posX > 1275 && posX <= 1396){
                moverInterfaz(0,0);
             }
            else if( posX > 281 && posX <= 1275){
                moverInterfaz(velocity.x*deltaTime,velocity.y*deltaTime);
            }
            else if(posX <= 281){
                moverInterfaz(0,velocity.y*deltaTime);
            }
            else if(posY > 378 && posX > 1467 && posX < 1468){
                setInterfaz(posX - 180.f, posY - 100.f);
            }
            else if(posX >= 1468){
                moverInterfaz(0,0);
            }
        }
        //boss bosque
        else if(zonaMapa == 4){
           if(posX > 101 && posX <= 110){
                setInterfaz(posX + 250.f, posY - 100.f);
             }
             else if(posX > 110 && posX <= 345){
                moverInterfaz(0,0);
             }
             else if( posX > 345 && posX < 481){
                moverInterfaz(velocity.x*deltaTime,velocity.y*deltaTime);
            }
            else if(posX >= 481){
                moverInterfaz(0,velocity.y*deltaTime);
            }
        }

        //boss montaña
        else if(zonaMapa == 5){
            if(posX > 74 && posX <= 75){
                setInterfaz(posX + 230.f, posY - 100.f);
             }
             else if(posX > 75 && posX <= 296){
                moverInterfaz(0,0);
             }
             else if(posX > 296 && posX < 455){
                moverInterfaz(velocity.x*deltaTime,velocity.y*deltaTime);
             }
             else if(posX >= 455){
                moverInterfaz(0,velocity.y*deltaTime);
             }
        }
    }



    motor->setViewPlayerPos(view.getCenter().x, view.getCenter().y);
    setPuntos(puntosVida, puntosTotalV, vida, 'v');
    setPuntos(puntosMana, puntosTotalM, mana, 'm');
    setDinero(cantDinero);
    setNumPoti(numPotiVida, pocionVida, 'v');
    setNumPoti(numPotiMana, pocionMana, 'm');
    this->numPotiVida = numPotiVida;
    this->numPotiMana = numPotiMana;
    this->cantDinero = cantDinero;
    this->cantFlechas = cantFlechas;

    float puntosArmadura = 0;

    if(equipado.size() != 0){
        for(unsigned int i = 0; i < equipado.size(); i++){
            if(equipado[i]->getType() == "Proyectil"&& equipado[i]->getName()==ataqueSecundarioSelected){
                
                setArmaS(equipado[i]->getColumna(),equipado[i]->getFila());
                setFlechas(cantFlechas);
            }

            if(equipado[i]->getType() == "Principal"){
                
                setArmaP(equipado[i]->getColumna(),equipado[i]->getFila());
            }

            if(equipado[i]->getType() == "Magia"&& equipado[i]->getName()==ataqueSecundarioSelected){   
               
                setArmaS(equipado[i]->getColumna(),equipado[i]->getFila());
            }
          
        }
                
        vidaT = puntosTotalV;
        manaT = puntosTotalM;
        ptosVida = puntosVida;
        ptosMana = puntosMana;
    }

    
}

void Interfaz::draw(){
    
    motor->window.setView(view);
    motor->drawSprite(pocionVida);
    motor->drawSprite(pocionMana);
    motor->drawSprite(armaP);
    motor->drawSprite(armaS);
    motor->drawRectangleShape(marco);
    motor->drawRectangleShape(marco2);
    motor->drawRectangleShape(vidaTotal);
    motor->drawRectangleShape(manaTotal);
    motor->drawRectangleShape(vida);
    motor->drawRectangleShape(mana);
    motor->drawRectangleShape(vidaTotal);
    motor->drawText(label);
    motor->drawText(label2);
    motor->drawText(numVidas);
    motor->drawText(numMana);
    motor->drawSprite(dinero);
    motor->drawText(cantMonedas);
    motor->drawSprite(flechas);
    motor->drawText(numFlechas);
}

// :::::METODOS::::

void Interfaz::createView(float x, float y){
    view.setCenter(std::floor(x),std::floor(y));
    view.zoom(0.6f);
}

void Interfaz::setView(float x, float y){
    view.setCenter(std::floor(x),std::floor(y));
    setInterfaz(std::floor(x),std::floor(y));
    motor->window.setView(view);
}

sf::Vector2f Interfaz::getView(){
    return sf::Vector2f(view.getCenter().x, view.getCenter().y);
}

void Interfaz::createBarras(){
    //crear barras de de vida y mana

    // x positiva - derecha
    // y positiva - abajo
    float y1,y2;

    y1 = view.getCenter().y - 220.f;
    y2 = view.getCenter().y - 180.f;

    maxptosVidaPixel = 100.f;
    maxManaPixel = 100.f;


    vidaTotal = sf::RectangleShape(sf::Vector2f(maxptosVidaPixel,15.f));
    vidaTotal.setFillColor(sf::Color::Transparent);
    vidaTotal.setOutlineThickness(0.8);
    vidaTotal.setOutlineColor(sf::Color::Red);
    vidaTotal.setOrigin(0,0);
    vidaTotal.setPosition(view.getCenter().x - 220.f,y1 + 15.f);

    manaTotal = sf::RectangleShape(sf::Vector2f(maxManaPixel,15.f));
    manaTotal.setFillColor(sf::Color::Transparent);
    manaTotal.setOutlineThickness(0.8);
    manaTotal.setOutlineColor(sf::Color::Blue);
    manaTotal.setOrigin(0,0);
    manaTotal.setPosition(view.getCenter().x - 220.f,y2 + 5.f);

    //rellena segun la vida/mana que tenga    
    vida = sf::RectangleShape(sf::Vector2f(maxptosVidaPixel,15.f));
    vida.setFillColor(sf::Color::Red);
    vida.setOrigin(0,0);
    vida.setPosition(view.getCenter().x - 220.f,y1 + 15.f);

    mana = sf::RectangleShape(sf::Vector2f(maxManaPixel,15.f));
    mana.setFillColor(sf::Color::Blue);
    mana.setOrigin(0,0);
    mana.setPosition(view.getCenter().x - 220.f,y2 + 5.f);

    //muestra con texto los puntos de vida y mana
    ptosVida = vidaT;
    ptosMana = manaT;
    label = sf::Text();
    label2 = sf::Text();
    setPuntos(ptosVida, vidaT, vida, 'v');
    setPuntos(ptosMana, manaT, mana, 'm');
}


void Interfaz::createArmaP(int posArmaPY, int posArmaPX){
     float x1, y1;
        x1 = view.getCenter().x - 50.f;
        y1 = view.getCenter().y - 200.f;
        
        marco = sf::RectangleShape(sf::Vector2f(32.f, 32.f));
        marco.setFillColor(sf::Color::Transparent);
        marco.setOutlineThickness(0.8);
        marco.setOutlineColor(sf::Color::White);
        marco.setOrigin(0,0);
        marco.setPosition(x1,y1);

    if(posArmaPX != -1 && posArmaPY != -1){
        armaP = sf::Sprite(texture);
        armaP.setTextureRect(sf::IntRect(posArmaPY * 32, posArmaPX * 32, 32, 32));
        armaP.setPosition(x1,y1);
    }
}

void Interfaz::createArmaS(int posArmaSY, int posArmaSX){
    float x1, y1;
        x1 = view.getCenter().x + 30.f;
        y1 = view.getCenter().y - 200.f;

        marco2 = sf::RectangleShape(sf::Vector2f(32.f, 32.f));
        marco2.setFillColor(sf::Color::Transparent);
        marco2.setOutlineThickness(0.8);
        marco2.setOutlineColor(sf::Color::White);
        marco2.setOrigin(0,0);
        marco2.setPosition(x1,y1);

        
    if(posArmaSX != -1 && posArmaSY != -1){
        armaS = sf::Sprite(texture);
        armaS.setTextureRect(sf::IntRect(posArmaSY* 32, posArmaSX * 32, 32, 32));
        armaS.setPosition(x1,y1);
    }
}

void Interfaz::createPociones(){

    //Y creo el spritesheet a partir de la imagen anterior
    pocionVida = sf::Sprite(texture);
    pocionMana = sf::Sprite(texture);
    
    //Cojo el sprite que me interesa por defecto del sheet
    pocionVida.setTextureRect(sf::IntRect(8 * 32, 1 * 32, 32, 32));
    pocionMana.setTextureRect(sf::IntRect(9* 32, 1 * 32, 32, 32));

    float x1,y1,x2,y2;

    x1 = view.getCenter().x + 140.f;
    x2 = view.getCenter().x + 140.f;
    y1 = view.getCenter().y - 220.f;
    y2 = view.getCenter().y - 180.f;
   
    pocionVida.setPosition(x1, y1);
    pocionMana.setPosition(x2, y2);

    //mostrar cantidad de pociones

    setNumPoti(numPotiVida,pocionVida,'v');
    setNumPoti(numPotiMana,pocionMana,'m');
    
}

void Interfaz::createDinero(){
    dinero = sf::Sprite(texture);
    dinero.setTextureRect(sf::IntRect(10 * 32, 1 * 32, 32, 32));

    dinero.setPosition(manaTotal.getPosition().x, manaTotal.getPosition().y + 20.f);

    setDinero(cantDinero);

}

void Interfaz::createFlechas(){
    flechas = sf::Sprite(texture);
    flechas.setTextureRect(sf::IntRect(11*32, 1 * 32, 32, 32));

    flechas.setPosition(marco2.getPosition().x + 35.f, marco2.getPosition().y + 5.f);

    setFlechas(cantFlechas);
    
}

//pasa el numero de pociones, el sprite de la pocion para apartir de esta obtener la posicion, y el tipo de si es vida o mana
void Interfaz::setNumPoti(int numPoti, sf::Sprite pocion, char tipo){
    std::string n;
    std::ostringstream np;


    np << numPoti;
    n = np.str();
    
    if(tipo == 'v'){
        numVidas = sf::Text();
        numVidas.setFont(fuente);
        numVidas.setString('x'+n);
        numVidas.setCharacterSize(14);
        numVidas.setColor(sf::Color::White);
        numVidas.setStyle(sf::Text::Bold);
        numVidas.setPosition(pocion.getPosition().x + 35.f,pocion.getPosition().y - 10.f);
    }
    else if(tipo == 'm'){
        numMana = sf::Text();
        numMana.setFont(fuente);
        numMana.setString('x'+n);
        numMana.setCharacterSize(14);
        numMana.setColor(sf::Color::White);
        numMana.setStyle(sf::Text::Bold);
        numMana.setPosition(pocion.getPosition().x + 35.f,pocion.getPosition().y - 10.f);
    }
    
}

//pasa la cantidad de puntos actuales del personaje, los puntos totales, la barra para apartir de esta obtener la posicion, y el tipo de si es vida o mana
void Interfaz::setPuntos(float puntos, float puntosTotal, sf::RectangleShape barra, char tipo){

    std::string p, pT;
    std::ostringstream ss, pp;
    ss << puntos;
    p = ss.str();
    pp << puntosTotal;
    pT = pp.str();
    
    if(tipo == 'v'){
        label.setFont(fuente);
        label.setString(p+"/" + pT);
        label.setCharacterSize(14);
        label.setColor(sf::Color::White);
        label.setStyle(sf::Text::Bold);
        label.setPosition(barra.getPosition().x + 35.f,barra.getPosition().y);
    }
    else if(tipo == 'm'){
        label2.setFont(fuente);
        label2.setString(p+"/" + pT);
        label2.setCharacterSize(14);
        label2.setColor(sf::Color::White);
        label2.setStyle(sf::Text::Bold);
        label2.setPosition(barra.getPosition().x + 35.f,barra.getPosition().y);
    }
    

}

//pasa la cantidad de dinero 
void Interfaz::setDinero(int cantDinero){
    std::string n;
    std::ostringstream np;

    np << cantDinero;
    n = np.str();

    cantMonedas = sf::Text();
    cantMonedas.setFont(fuente);
    cantMonedas.setString(n);
    cantMonedas.setCharacterSize(14);
    cantMonedas.setColor(sf::Color::White);
    cantMonedas.setStyle(sf::Text::Bold);
    cantMonedas.setPosition(dinero.getPosition().x + 40.f, dinero.getPosition().y + 10.f);
}

void Interfaz::setFlechas(int cantFlechas){
    std::string n;
    std::ostringstream np;

    np << cantFlechas;
    n = np.str();

    numFlechas = sf::Text();
    numFlechas.setFont(fuente);
    numFlechas.setString("x"+n);
    numFlechas.setCharacterSize(14);
    numFlechas.setColor(sf::Color::White);
    numFlechas.setStyle(sf::Text::Bold);
    numFlechas.setPosition(flechas.getPosition().x + 20.f, flechas.getPosition().y - 15.f);
}

void Interfaz::setArmaP(int posX, int posY){
    armaP.setTextureRect(sf::IntRect(posX * 32, posY * 32, 32, 32));
}

void Interfaz::setArmaS(int posX, int posY){
    armaS.setTextureRect(sf::IntRect(posX * 32, posY * 32, 32, 32));
}
// se pasa el danio recibido de la vida, hace una regla de tres para sacar el tamano del rectangulo y actualiza el texto con los puntos
float Interfaz::quitarVida(float danioRecibido){
    if(ptosVida > 0){
        float puntosVida = ptosVida;
        ptosVida = ((ptosVida - danioRecibido)*maxptosVidaPixel)/vidaT;
        
        
        if(ptosVida <= 0){
            ptosVida = 0;
        }

        vida.setSize(sf::Vector2f(ptosVida,vida.getSize().y));

        std::string v, vT;
        std::ostringstream ss, pp;
        ptosVida = round(ptosVida);
        ss << ptosVida;
        v = ss.str();
        pp << vidaT;
        vT = pp.str();
        
        label.setString(v+"/" + vT);

        ptosVida = puntosVida - danioRecibido;
    }

    return ptosVida;
}

//se pasa el mana gastado, hace una regla de tres para sacar el tamano del rectangulo y actualiza el texto con los puntos
 float Interfaz::quitarMana(float manaConsumido){
     if(ptosMana > 0){
        float puntosMana = ptosMana;
        ptosMana = ((ptosMana - manaConsumido)*maxManaPixel)/manaT;

        if(ptosMana <= 0){
            ptosMana = 0;
        }

        mana.setSize(sf::Vector2f(ptosMana,mana.getSize().y));
 
        std::string m, mT;
        std::ostringstream mm, nn;
        ptosMana = round(ptosMana);
        mm << ptosMana;
        m = mm.str();
        nn << manaT;
        mT = nn.str();
        label2.setString(m+"/" + mT);

        ptosMana = puntosMana - manaConsumido;

    }
    return ptosMana;
 }

 float Interfaz::sumarVida(float vidaSumada){

    float puntosVida = ptosVida;
    ptosVida = ((ptosVida + vidaSumada)*maxptosVidaPixel)/vidaT;

    if(ptosVida>vidaT){
        ptosVida=vidaT;
    }


    vida.setSize(sf::Vector2f(ptosVida,vida.getSize().y));

    std::string v, vT;
    std::ostringstream ss, pp;
    ptosVida = round(ptosVida);
    ss << ptosVida;
    v = ss.str();
    pp << vidaT;
    vT = pp.str();
    
    label.setString(v+"/" + vT);

    ptosVida = puntosVida + vidaSumada;
    return ptosVida;
}

//se pasa el mana gastado, hace una regla de tres para sacar el tamano del rectangulo y actualiza el texto con los puntos
 float Interfaz::sumarMana(float manaSumado){
    float puntosMana = ptosMana;
    
    ptosMana = ((ptosMana + manaSumado)*maxManaPixel)/manaT;

    if(ptosMana>manaT){
        ptosMana=manaT;
    }

    mana.setSize(sf::Vector2f(ptosMana,mana.getSize().y));

    std::string m, mT;
    std::ostringstream mm, nn;
    ptosMana = round(ptosMana);
    mm << ptosMana;
    m = mm.str();
    nn << manaT;
    mT = nn.str();
    label2.setString(m+"/" + mT);

    ptosMana = puntosMana + manaSumado;
    return ptosMana;
 }

//se pasa el mana gastado, hace una regla de tres para sacar el tamano del rectangulo y actualiza el texto con los puntos
 void Interfaz::setMana(float puntosMana){
    ptosMana = (puntosMana*maxManaPixel)/manaT;

    mana.setSize(sf::Vector2f(ptosMana,mana.getSize().y));
    std::string m, mT;
    std::ostringstream mm, nn;
    puntosMana = round(puntosMana);
    mm << puntosMana;
    m = mm.str();
    nn << manaT;
    mT = nn.str();
    label2.setString(m+"/" + mT);

 }

void Interfaz::setVida(float puntosVida){

    ptosVida = (puntosVida*maxptosVidaPixel)/vidaT;

    vida.setSize(sf::Vector2f(ptosVida,vida.getSize().y));

    std::string v, vT;
    std::ostringstream ss, pp;
    puntosVida = round(puntosVida);
    ss << puntosVida;
    v = ss.str();
    pp << vidaT;
    vT = pp.str();
    
    label.setString(v+"/" + vT);

}

float Interfaz::usarPotiVida(){
    float pasa_v=0;
    if(numPotiVida > 0){

        

        pasa_v=this->sumarVida(20);

        numPotiVida--;
        std::string nv;
        std::ostringstream npv;
        npv << numPotiVida;
        nv = npv.str();
        numVidas.setString('x'+nv);
    }
    return pasa_v;
}

float Interfaz::usarPotiMana(){
    float pasa_m=0;
    if(numPotiMana > 0){

    

        pasa_m=this->sumarMana(30);


        numPotiMana--;
        std::string nm;
        std::ostringstream npm;
        npm << numPotiMana;
        nm = npm.str();
        numMana.setString('x'+nm);
    }
    return pasa_m;
}

void Interfaz::moverInterfaz(float x, float y){
    
    view.move(x,y);
    vida.move(x,y);
    vidaTotal.move(x,y);
    label.move(x,y);
    mana.move(x,y);
    manaTotal.move(x,y);
    label2.move(x,y);
    armaP.move(x,y);
    armaS.move(x,y);
    marco.move(x,y);
    marco2.move(x,y);
    pocionVida.move(x,y);
    pocionMana.move(x,y);
    numVidas.move(x,y);
    numMana.move(x,y);
    dinero.move(x,y);
    cantMonedas.move(x,y);
    flechas.move(x,y);
    numFlechas.move(x,y);
    
}

void Interfaz::setInterfaz(float x, float y){

    view.setCenter(x,y);
    // x positiva - derecha
    // y positiva - abajo


    vida.setPosition(x- 220.f,y - 150.f);
    vidaTotal.setPosition(x - 220.f,y - 150.f);
    label.setPosition(vida.getPosition().x + 35.f,vida.getPosition().y);
    mana.setPosition(vida.getPosition().x,y - 110.f);
    manaTotal.setPosition(vida.getPosition().x,y - 110.f);
    label2.setPosition(manaTotal.getPosition().x + 35.f,manaTotal.getPosition().y);
    armaP.setPosition(x - 50.f,y - 150.f);
    armaS.setPosition(x + 30.f,y - 150.f);
    marco.setPosition(armaP.getPosition().x,armaP.getPosition().y);
    marco2.setPosition(armaS.getPosition().x,armaS.getPosition().y);
    pocionVida.setPosition(x + 140.f,y - 150.f);
    pocionMana.setPosition(x + 140.f,y - 110.f);
    numVidas.setPosition(pocionVida.getPosition().x + 35.f,pocionVida.getPosition().y - 10.f);
    numMana.setPosition(pocionMana.getPosition().x + 35.f,pocionMana.getPosition().y - 10.f);
    dinero.setPosition(manaTotal.getPosition().x, manaTotal.getPosition().y + 20.f);
    cantMonedas.setPosition(dinero.getPosition().x + 40.f, dinero.getPosition().y + 10.f);
    flechas.setPosition(marco2.getPosition().x + 35.f, marco2.getPosition().y + 5.f);
    numFlechas.setPosition(flechas.getPosition().x + 20.f, flechas.getPosition().y - 15.f);
}

float Interfaz::getMana(){
    return ptosMana;
}