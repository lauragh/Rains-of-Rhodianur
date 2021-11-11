#include "interfaz.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cmath>

//constructor
Interfaz::Interfaz(int x, int y,double puntosVida, double puntosMana, int cantDinero) {
    //Cargo la imagen donde reside la textura del sprite
    std::string textureName = "resources/sprite sheet.png";
    if (!texture.loadFromFile(textureName)) {
        std::cerr << "Error cargando la imagen" << textureName << std::endl;
    exit(0);
    }
    //anadimos la fuente de texto
    fuente = sf::Font();
    std::string fontname = "resources/dungeon.TTF";
    if (!fuente.loadFromFile(fontname)){
       std::cerr << "Error cargando la fuente " <<fontname << std::endl;
    exit(0);
    }
    vidaT = puntosVida;
    manaT = puntosMana;
    ptosVida = vidaT;
    ptosMana = manaT;
    this->cantDinero = cantDinero;
    
    createBarras();
    createArmas();
    createPociones();
    createDinero();
    
}

void Interfaz::update(sf::Vector2f mov){
    moverInterfaz(mov);
}

void Interfaz::draw(sf::RenderWindow &window){
    window.setView(view);
    window.draw(pocionVida);
    window.draw(pocionMana);
    window.draw(armaP);
    window.draw(armaS);
    window.draw(marco);
    window.draw(marco2);
    window.draw(vidaTotal);
    window.draw(manaTotal);
    window.draw(vida);
    window.draw(mana);
    window.draw(label);
    window.draw(label2);
    window.draw(numVidas);
    window.draw(numMana);
    window.draw(dinero);
    window.draw(cantMonedas);
}

// :::::METODOS::::


void Interfaz::createBarras(){
    //crear barras de de vida y mana
    float y1,y2;

    y1 = view.getCenter().y - 220.f;
    y2 = view.getCenter().y - 180.f;

    maxptosVidaixel = 100.f;
    maxManaPixel = 100.f;


    vidaTotal = sf::RectangleShape(sf::Vector2f(maxptosVidaixel,15.f));
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
    vida = sf::RectangleShape(sf::Vector2f(maxptosVidaixel,15.f));
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
    anadirPuntos(ptosVida, vidaT, vida, 'v');
    anadirPuntos(ptosMana, manaT, mana, 'm');

}

void Interfaz::createArmas(){
    armaP = sf::Sprite(texture);
    armaS = sf::Sprite(texture);

    armaP.setTextureRect(sf::IntRect(0* 32, 0 * 32, 32, 32));
    armaS.setTextureRect(sf::IntRect(3* 32, 0 * 32, 32, 32));
    
    float x3,y3,x4,y4;

    x3 = view.getCenter().x - 50.f;
    x4 = view.getCenter().x + 30.f;
    y3 = view.getCenter().y - 200.f;
    y4 =  y3;

    armaP.setPosition(x3,y3);
    armaS.setPosition(x4,y4);

    //Crea los marcos
    marco = sf::RectangleShape(sf::Vector2f(32.f, 32.f));
    marco.setFillColor(sf::Color::Transparent);
    marco.setOutlineThickness(0.8);
    marco.setOutlineColor(sf::Color::White);
    marco.setOrigin(0,0);
    marco.setPosition(x3,y3);


    marco2 = sf::RectangleShape(sf::Vector2f(32.f, 32.f));
    marco2.setFillColor(sf::Color::Transparent);
    marco2.setOutlineThickness(0.8);
    marco2.setOutlineColor(sf::Color::White);
    marco2.setOrigin(0,0);
    marco2.setPosition(x4,y4);
}

void Interfaz::createPociones(){

    //Y creo el spritesheet a partir de la imagen anterior
    pocionVida = sf::Sprite(texture);
    pocionMana = sf::Sprite(texture);
    
    //Cojo el sprite que me interesa por defecto del sheet
    pocionVida.setTextureRect(sf::IntRect(1 * 32, 0 * 32, 32, 32));
    pocionMana.setTextureRect(sf::IntRect(2* 32, 0 * 32, 32, 32));

    float x1,y1,x2,y2;

    x1 = view.getCenter().x + 140.f;
    x2 = view.getCenter().x + 140.f;
    y1 = view.getCenter().y - 220.f;
    y2 = view.getCenter().y - 180.f;
   
    pocionVida.setPosition(x1, y1);
    pocionMana.setPosition(x2, y2);

    //mostrar cantidad de pociones
    numPotiVida = 2;
    numPotiMana = 3;

    anadirNumPotis(numPotiVida,pocionVida,'v');
    anadirNumPotis(numPotiMana,pocionMana,'m');
    
}

void Interfaz::createDinero(){
    dinero = sf::Sprite(texture);
    dinero.setTextureRect(sf::IntRect(4 * 32, 0 * 32, 32, 32));

    dinero.setPosition(manaTotal.getPosition().x, manaTotal.getPosition().y + 10.f);

    anadirDinero(cantDinero,dinero);



}
void Interfaz::anadirNumPotis(int numPoti, sf::Sprite pocion, char tipo){
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

void Interfaz::anadirPuntos(double puntos, double puntosTotal, sf::RectangleShape barra, char tipo){

    std::string p, pT;
    std::ostringstream ss, pp;
    ss << puntos;
    p = ss.str();
    pp << puntosTotal;
    pT = pp.str();
    
    if(tipo == 'v'){
        label.setFont(fuente);
        label.setString(pT+"/" + pT);
        label.setCharacterSize(14);
        label.setColor(sf::Color::White);
        label.setStyle(sf::Text::Bold);
        label.setPosition(barra.getPosition().x + 35.f,barra.getPosition().y);
    }
    else if(tipo == 'm'){
        label2.setFont(fuente);
        label2.setString(pT+"/" + pT);
        label2.setCharacterSize(14);
        label2.setColor(sf::Color::White);
        label2.setStyle(sf::Text::Bold);
        label2.setPosition(barra.getPosition().x + 35.f,barra.getPosition().y);
    }
    

}

void Interfaz::anadirDinero(int cantDinero, sf::Sprite dinero){
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
void Interfaz::quitarVida(double danioRecibido){
    if(ptosVida > 0){
        ptosVida = ((ptosVida - danioRecibido)*maxptosVidaixel)/vidaT;
        
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
    }
}

 void Interfaz::quitarMana(double manaConsumido){
     if(ptosMana > 0){

        ptosMana = ((ptosMana - manaConsumido)*maxptosVidaixel)/manaT;

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

    }
 }

void Interfaz::usarPotiVida(){
    if(numPotiVida > 0){
        numPotiVida--;
        std::string nv;
        std::ostringstream npv;
        npv << numPotiVida;
        nv = npv.str();
        numVidas.setString('x'+nv);
    }
}

void Interfaz::usarPotiMana(){
    if(numPotiMana > 0){
        numPotiMana--;
        std::string nm;
        std::ostringstream npm;
        npm << numPotiMana;
        nm = npm.str();
        numMana.setString('x'+nm);
    }
}

void Interfaz::moverInterfaz(sf::Vector2f mov){
    vida.move(mov);
    vidaTotal.move(mov);
    label.move(mov);
    mana.move(mov);
    manaTotal.move(mov);
    label2.move(mov);
    armaP.move(mov);
    armaS.move(mov);
    marco.move(mov);
    marco2.move(mov);
    pocionVida.move(mov);
    pocionMana.move(mov);
    numVidas.move(mov);
    numMana.move(mov);
    view.move(mov);
    dinero.move(mov);
    cantMonedas.move(mov);
}