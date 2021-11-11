#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cmath>

#include "../states/shop_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"

ShopState::ShopState(GameData data, int idTienda): datagame(data){
    this->idTienda = idTienda;
}

void ShopState::Init(){
   GameState *estadoJuego = GameState::Instance();
    estadoJuego->music.pause();
   
    motor = Motor2D::Instance();
    motor->addTexture("tienda", "resources/tienda.png");

    tiendaBG.setTexture(motor->getTexture("tienda"));
    tiendaBG.setOrigin(0,0);

    tiendaBG.setPosition(motor->view.getCenter().x - 245.f, motor->view.getCenter().y - 220.f);
    tiendaBG.setScale(1,1);
    tiendaBG.scale(1.5f,2.f);
 
    fuente = motor->getFont("Dungeon");

    sf::Sprite sprite;
    sprite.setTexture(motor->getTexture("sprite_sheet"));
    sprite.scale(2.f,2.f);

    dineroJugador.setTexture(motor->getTexture("sprite_sheet"));
    dineroJugador.setTextureRect(sf::IntRect(10 * 32, 1 * 32, 32, 32));
    dineroJugador.setPosition(motor->view.getCenter().x + 100.f, motor->view.getCenter().y - 250.f);

    cantDineroJugador = sf::Text();
    cantDineroJugador.setFont(motor->getFont("Dungeon"));
    cantDineroJugador.setCharacterSize(18);
    cantDineroJugador.setString(num2String(estadoJuego->jugador->getMoney()));
    cantDineroJugador.setPosition(dineroJugador.getPosition().x + 40.f,dineroJugador.getPosition().y + 10.f);
    cantDineroJugador.setStyle(sf::Text::Bold);


    std::vector<std::string> tipo;
    std::vector<std::string> nombreObjetos;


    //TIENDA DE COMIDA
    if(idTienda == 262){
        objetosTienda.push_back(datagame->objects["Manzana"]);
        objetosTienda.push_back(datagame->objects["Muslo de pollo"]);
        objetosTienda.push_back(datagame->objects["Chuleta"]);
        objetosTienda.push_back(datagame->objects["Pierna de pavo"]);
        objetosTienda.push_back(datagame->objects["Costilla de vaca"]);
        objetosTienda.push_back(datagame->objects["Pescado asado"]);
        objetosTienda.push_back(datagame->objects["Huevo cocido"]);
        objetosTienda.push_back(datagame->objects["Queso"]);
        objetosTienda.push_back(datagame->objects["Zanahoria"]);
        objetosTienda.push_back(datagame->objects["Mazorca de maíz"]);

        tipo.push_back("Comida");
        addTienda(sprite,tipo,idTienda);

        for(int i = 0; i < objetosTienda.size(); i++){
            nombreObjetos.push_back(objetosTienda[i]->getName());
        }
    }
    //TIENDA DE MAGIA
    else if(idTienda == 257){
        objetosTienda.push_back(datagame->objects["Pocion Vida"]);
        objetosTienda.push_back(datagame->objects["Pocion Mana"]);
        objetosTienda.push_back(datagame->objects["Amuleto Mágico"]);
        objetosTienda.push_back(datagame->objects["Collar Colmillos"]);

        
        tipo.push_back("Pocion");
        tipo.push_back("Amuleto");
        addTienda(sprite,tipo,idTienda);

        for(int i = 0; i < objetosTienda.size(); i++){
            nombreObjetos.push_back(objetosTienda[i]->getName());
        }
    }
    //HERRERIA
    else if(idTienda == 263){
        std::vector <Object*> objetosCheck;

        objetosCheck.push_back(datagame->objects["Hacha oxidada"]);
        objetosCheck.push_back(datagame->objects["Hachuela"]);
        objetosCheck.push_back(datagame->objects["Hacha de guerra"]);
        objetosCheck.push_back(datagame->objects["Arco gastado"]);
        objetosCheck.push_back(datagame->objects["Arco de cazador"]);
        objetosCheck.push_back(datagame->objects["Ballesta"]);
        objetosCheck.push_back(datagame->objects["Casco con cuernos"]);
        objetosCheck.push_back(datagame->objects["Pechera hierro"]);
        objetosCheck.push_back(datagame->objects["Guantes mágicos"]);
        objetosCheck.push_back(datagame->objects["Perneras de cota de malla"]);
        objetosCheck.push_back(datagame->objects["Flechas"]);

        for(int i = 0; i < (int) estadoJuego->jugador->getObjetosDisponibles().size(); i++){
            for(int j = 0; j < (int) objetosCheck.size(); j++){
                if(estadoJuego->jugador->getObjetosEquipados()[i]->getName() != "Flecha" && estadoJuego->jugador->getObjetosDisponibles()[i] == objetosCheck[j]){
                    // Deletes the second element (vec[1]) vec.erase(vec.begin() + 1);
                    objetosCheck.erase(objetosCheck.begin() + j);
                }
            }
        }

        for(int i = 0; i < (int) estadoJuego->jugador->getObjetosEquipados().size(); i++){
            for(int j = 0; j < (int) objetosCheck.size(); j++){
                if(estadoJuego->jugador->getObjetosEquipados()[i]->getName() != "Flecha" && estadoJuego->jugador->getObjetosEquipados()[i] == objetosCheck[j]){
                    // Deletes the second element (vec[1]) vec.erase(vec.begin() + 1);
                    objetosCheck.erase(objetosCheck.begin() + j);
                }
            }
        }

        for(int i = 0; i < (int) objetosCheck.size(); i++){
            objetosTienda.push_back(datagame->objects[objetosCheck[i]->getName()]);
            nombreObjetos.push_back(datagame->objects[objetosCheck[i]->getName()]->getName());    
        }
        
        tipo.push_back("Principal");
        tipo.push_back("Proyectil");
        tipo.push_back("Casco");
        tipo.push_back("Pechera");
        tipo.push_back("Brazos");
        tipo.push_back("Piernas");
        tipo.push_back("Flechas");

        addTienda(sprite,tipo,idTienda);

    }
    else if(idTienda == 268){
        if(estadoJuego->mapaBosque == false){        
            objetosTienda.push_back(datagame->objects["Mapa Bosque"]);
            nombreObjetos.push_back("Mapa Bosque");    
            tipo.push_back("Mapa");
            addTienda(sprite,tipo,idTienda);
        }
        
    }

    else if(idTienda == 269){
        if(estadoJuego->mapaMontana == false){
            objetosTienda.push_back(datagame->objects["Mapa Montaña"]);
            nombreObjetos.push_back("Mapa Montana");   
            tipo.push_back("Mapa");
            addTienda(sprite,tipo,idTienda);
      
        }   
    }
    
    objetoSeleccionado = 1;
    int contador = 0;
    int sigPosX = 0;

    sf::Text texto;
    texto.setFont(motor->getFont("Dungeon"));
    texto.setStyle(sf::Text::Bold);
    texto.setOrigin(0,0);
    texto.setCharacterSize(16);

    for(unsigned int i = 0; i < nombreObjetos.size(); i++){
        texto.setString(nombreObjetos[i]);
        if(nombreObjetos[i] == "Hacha oxidada"){
            texto.setString("Hacha\noxidada");
        }
        else if(nombreObjetos[i] == "Hacha de guerra"){
            texto.setString("hacha\nde guerra");
        }
        else if(nombreObjetos[i] == "Arco gastado"){
            texto.setString("Arco\ngastado");
        }
        else if(nombreObjetos[i] == "Arco de cazador"){
            texto.setString("Arco\nde cazador");
        }
        else if(nombreObjetos[i] == "Guantes mágicos"){
            texto.setString("Guantes\nmagicos");
        }
        else if(nombreObjetos[i] == "Casco con cuernos"){
            texto.setString("Casco\ncon cuernos");
        }
        else if(nombreObjetos[i] == "Perneras de cota de malla"){
            texto.setString("Perneras\nde cota de malla");
        }
        else if(nombreObjetos[i] == "Pechera hierro"){
            texto.setString("Pechera\nhierro");
        }
        else if(nombreObjetos[i] == "Arco de cazador"){
            texto.setString("Arco\nde cazador");
        }
        else if(nombreObjetos[i] == "Muslo de pollo"){
            texto.setString("Muslo\nde pollo");
        }
        else if(nombreObjetos[i] == "Pierna de pavo"){
            texto.setString("Pierna\nde pavo");
        }
        else if(nombreObjetos[i] == "Costilla de vaca"){
            texto.setString("Costilla\nde vaca");
        }   
        else if(nombreObjetos[i] == "Pescado asado"){
            texto.setString("Pescado\nasado");
        }   
        else if(nombreObjetos[i] == "Huevo cocido"){
            texto.setString("Huevo\ncocido");
        }   
        else if(nombreObjetos[i] == "Mazorca de maíz"){
            texto.setString("Mazorca\nde maiz");
        }
        else if(nombreObjetos[i] == "Amuleto Mágico"){
            texto.setString("Amuleto Magico");
        }

        
        if(idTienda == 257){
            if(contador == 2){
                sigPosX = 0;
                texto.setPosition(motor->view.getCenter().x - 145.f - ((sigPosX)*-1),motor->view.getCenter().y + 100.f);
            }
            else if(contador > 2){
                texto.setPosition(motor->view.getCenter().x - 145.f - ((sigPosX)*-1),motor->view.getCenter().y + 100.f);
            }
            
            else{
                texto.setPosition(motor->view.getCenter().x - 145.f - ((sigPosX)*-1),motor->view.getCenter().y - 100.f);
            }
            sigPosX += 150.f;

        }
        else if(idTienda == 262 || idTienda == 263){
            if(contador == 5){
                sigPosX = 0;
                texto.setPosition(motor->view.getCenter().x - 195.f - ((sigPosX)*-1),motor->view.getCenter().y + 100.f);
            }
            else if(contador > 5){
            texto.setPosition(motor->view.getCenter().x - 195.f - ((sigPosX)*-1),motor->view.getCenter().y + 100.f);
            }
            else{
                texto.setPosition(motor->view.getCenter().x - 195.f - ((sigPosX)*-1),motor->view.getCenter().y - 100.f);
            }
            sigPosX += 80.f;
        }
        else if(idTienda == 268 || idTienda == 269){
            texto.setPosition(motor->view.getCenter().x - 20.f,motor->view.getCenter().y - 100.f);
        }
        contador++;
        optionsTienda.push_back(texto);
    }

    bool mapaBosqueObtenido = estadoJuego->mapaBosque;
    bool mapaMontanaObtenido = estadoJuego->mapaMontana;

    if((!mapaBosqueObtenido && mapaMontanaObtenido) || (!mapaBosqueObtenido && !mapaMontanaObtenido) || (mapaBosqueObtenido && mapaMontanaObtenido)){
        if(idTienda != 268 && idTienda != 269){

            selector = sf::RectangleShape(sf::Vector2f(optionsTienda[0].getLocalBounds().width,optionsTienda[0].getLocalBounds().height + 5.f));
            selector.setFillColor(sf::Color::Transparent);
            selector.setFillColor(sf::Color::Transparent);
            selector.setOutlineThickness(0.8);
            selector.setOutlineColor(sf::Color::White);
            selector.setOrigin(0,0);
            selector.setPosition(optionsTienda[0].getPosition().x,optionsTienda[0].getPosition().y);
        }
    }
      
    if(idTienda != 268 && idTienda != 269){ 
        setEstadisticas();
    }

    
    objetoSeleccionado = 0;
    cont = 0;

    
}

void ShopState::setEstadisticas(){

    //VIDA

    labelVida = sf::Text();
    labelVida.setFont(motor->getFont("Dungeon"));
    labelVida.setStyle(sf::Text::Bold);
    labelVida.setOrigin(0,0);
    labelVida.setCharacterSize(16);
    labelVida.setString("Vida");
    labelVida.setPosition(tiendaBG.getPosition().x - 50.f, sprites[0].getPosition().y);

    aumentoVida = sf::Text();
    aumentoVida.setFont(motor->getFont("Dungeon"));
    aumentoVida.setStyle(sf::Text::Bold);
    aumentoVida.setOrigin(0,0);
    aumentoVida.setCharacterSize(16);
    aumentoVida.setPosition(labelVida.getPosition().x + 30.f, labelVida.getPosition().y);

    if(objetosTienda[0]->getStats().health != 0){
        aumentoVida.setString("+"+num2String(objetosTienda[0]->getStats().health));
    }

    //ARMADURA

    labelArmadura = sf::Text();
    labelArmadura.setFont(motor->getFont("Dungeon"));
    labelArmadura.setStyle(sf::Text::Bold);
    labelArmadura.setOrigin(0,0);
    labelArmadura.setCharacterSize(16);
    labelArmadura.setString("Armadura");
    labelArmadura.setPosition(tiendaBG.getPosition().x - 50.f, sprites[0].getPosition().y +30.f);

    aumentoArmadura = sf::Text();
    aumentoArmadura.setFont(motor->getFont("Dungeon"));
    aumentoArmadura.setStyle(sf::Text::Bold);
    aumentoArmadura.setOrigin(0,0);
    aumentoArmadura.setCharacterSize(16);
    aumentoArmadura.setPosition(labelArmadura.getPosition().x + 55.f, labelArmadura.getPosition().y);

    if(objetosTienda[0]->getStats().armour != 0){
        aumentoArmadura.setString("+"+num2String(objetosTienda[0]->getStats().armour));
    }

    //MANA 
    //motor->view.getCenter().x - 245.f
    labelMana = sf::Text();
    labelMana.setFont(motor->getFont("Dungeon"));
    labelMana.setStyle(sf::Text::Bold);
    labelMana.setOrigin(0,0);
    labelMana.setCharacterSize(16);
    labelMana.setString("Mana");
    labelMana.setPosition(tiendaBG.getPosition().x - 50.f, sprites[0].getPosition().y+60.f);

    aumentoMana = sf::Text();
    aumentoMana.setFont(motor->getFont("Dungeon"));
    aumentoMana.setStyle(sf::Text::Bold);
    aumentoMana.setOrigin(0,0);
    aumentoMana.setCharacterSize(16);
    aumentoMana.setPosition(labelMana.getPosition().x+ 35.f, labelMana.getPosition().y);

    if(objetosTienda[0]->getStats().mana != 0){
        aumentoMana.setString("+"+num2String(objetosTienda[0]->getStats().mana));
    }

  
    //DAÑO

    labelDanio = sf::Text();
    labelDanio.setFont(motor->getFont("Dungeon"));
    labelDanio.setStyle(sf::Text::Bold);
    labelDanio.setOrigin(0,0);
    labelDanio.setCharacterSize(16);
    labelDanio.setString("Danio");
    labelDanio.setPosition(tiendaBG.getPosition().x - 50.f, sprites[0].getPosition().y+90.f);

    aumentoDanio = sf::Text();
    aumentoDanio.setFont(motor->getFont("Dungeon"));
    aumentoDanio.setStyle(sf::Text::Bold);
    aumentoDanio.setOrigin(0,0);
    aumentoDanio.setCharacterSize(16);
    aumentoDanio.setPosition(labelDanio.getPosition().x+ 35.f, labelDanio.getPosition().y);

    if(objetosTienda[0]->getStats().mana != 0){
        aumentoMana.setString("+"+num2String(objetosTienda[0]->getStats().mana));
    }  
}

void ShopState::addTienda(sf::Sprite sprite, std::vector<std::string> tipo, int idTienda){
    int contador = 0;
    float sigPosX = 0;

    sf::Text coste;

    sf::Sprite monedaCoste;

    monedaCoste.setTexture(motor->getTexture("sprite_sheet"));
    monedaCoste.setTextureRect(sf::IntRect(10 * 32, 1 * 32, 32, 32));
    monedaCoste.scale(0.5f,0.5f);

    
    for(int i = 0; i < (int)objetosTienda.size(); i++){
        for(int j = 0; j < (int)tipo.size(); j++){
            if(objetosTienda[i]->getType() == tipo[j]){
                std::string m;
                std::ostringstream sm;

                sm << objetosTienda[i]->getCost();
                m = sm.str();
                coste.setFont(motor->getFont("Dungeon"));
                coste.setStyle(sf::Text::Bold);
                coste.setOrigin(0,0);
                coste.setCharacterSize(16);
                coste.setString(m);
                sprite.setTextureRect(sf::IntRect(objetosTienda[i]->getColumna()* 32, objetosTienda[i]->getFila()* 32, 32, 32));

                if(idTienda == 257){
                    if(contador == 2){
                        sigPosX = 0;
                        sprite.setPosition(motor->view.getCenter().x - 150.f - ((sigPosX)*-1),motor->view.getCenter().y + 120.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                    else if(contador > 2){
                        sprite.setPosition(motor->view.getCenter().x - 150.f - ((sigPosX)*-1),motor->view.getCenter().y + 120.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                   
                    else{
                        sprite.setPosition(motor->view.getCenter().x - 150.f - ((sigPosX)*-1),motor->view.getCenter().y - 70.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                    sigPosX += 150.f;

                }
                else if(idTienda == 262 || idTienda == 263){
                    if(contador == 5){
                        sigPosX = 0;
                        sprite.setPosition(motor->view.getCenter().x - 200.f - ((sigPosX)*-1),motor->view.getCenter().y + 120.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                    else if(contador > 5){
                        sprite.setPosition(motor->view.getCenter().x - 200.f - ((sigPosX)*-1),motor->view.getCenter().y + 120.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                    else{
                        sprite.setPosition(motor->view.getCenter().x - 200.f - ((sigPosX)*-1),motor->view.getCenter().y - 70.f);
                        monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                        coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                    }
                    sigPosX += 80.f;
                }
                else if(idTienda == 268 || idTienda == 269){
                    sprite.setPosition(motor->view.getCenter().x - 20.f,motor->view.getCenter().y - 70.f);
                    monedaCoste.setPosition(sprite.getPosition().x + 20.f, sprite.getPosition().y + 70.f);
                    coste.setPosition(monedaCoste.getPosition().x + 20.f, monedaCoste.getPosition().y);
                }
                
                sprites.push_back(sprite);
                costeObjetos.push_back(coste);
                monedasCoste.push_back(monedaCoste);
                contador++;
            }
        } 
    }
}


void ShopState::HandleInput()
    {
        GameState *estadoJuego = GameState::Instance();
        sf::Event event;

        while (motor->window.pollEvent(event))
        {
        
            switch (event.type) {

            //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    motor->window.close();
                    break;

                case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                     case sf::Keyboard::Left:
                        cont = 0;
                        moveLeft();
                        break;

                    case sf::Keyboard::Right:
                        cont = 0;
                        moveRight();
                        break;

                    case sf::Keyboard::Escape:

                        if(estadoJuego->musicaActiva){
                            estadoJuego->music.play();
                        }
                        datagame->states.popState();
                        break;

                    case sf::Keyboard::Return:

                        if(cont < 1){
                            nombre = optionsTienda[objetoSeleccionadoPressed()].getString();

                            optionsTienda[objetoSeleccionadoPressed()].setString( "Comprar?");
                            cont++;
                        }
                     
                        else{
                                comprar();
                                cont = 0;
                            }
                        
                        break;
                    //Cualquier tecla desconocida se imprime por pantalla su código
                    default:
                        break;
                }
            }
        }
    }

void ShopState::comprar(){
    GameState *estadoJuego = GameState::Instance();

    int dineroActual = estadoJuego->jugador->getMoney()-objetosTienda[objetoSeleccionadoPressed()]->getCost();

    if(estadoJuego->jugador->getMoney() >=  objetosTienda[objetoSeleccionadoPressed()]->getCost() && dineroActual >= 0){
        estadoJuego->jugador->setMoney(dineroActual);
        cantDineroJugador.setString(num2String(estadoJuego->jugador->getMoney()));
        if(objetosTienda[objetoSeleccionado]->getName() == "Pocion Vida"){
            estadoJuego->jugador->setPotis("v");
        }
        else if(objetosTienda[objetoSeleccionado]->getName() == "Pocion Mana"){
            estadoJuego->jugador->setPotis("m");
        }
        else if(objetosTienda[objetoSeleccionado]->getName() == "Flechas"){
            estadoJuego->jugador->setArrow(1);
        }
        else if(objetosTienda[objetoSeleccionado]->getType() == "Comida"){
            if(objetosTienda[objetoSeleccionado]->getStats().health != 0){
                if(estadoJuego->jugador->getVida() < estadoJuego->jugador->getVidaMax()){
                    if(estadoJuego->jugador->getVida()+ objetosTienda[objetoSeleccionado]->getStats().health >= estadoJuego->jugador->getVidaMax()){
                        estadoJuego->jugador->setVida(estadoJuego->jugador->getVidaMax());
                       estadoJuego->jugador->info->setVida(estadoJuego->jugador->getVidaMax());
                    }
                    else{
                        estadoJuego->jugador->setVida(estadoJuego->jugador->getVida() + objetosTienda[objetoSeleccionado]->getStats().health);
                        float vida = estadoJuego->jugador->info->sumarVida(objetosTienda[objetoSeleccionado]->getStats().health);

                    }
                }
            }
            if(objetosTienda[objetoSeleccionado]->getStats().mana != 0){
                if(estadoJuego->jugador->getMana() < estadoJuego->jugador->getManaMax()){
                   if(estadoJuego->jugador->getMana()+ objetosTienda[objetoSeleccionado]->getStats().mana >= estadoJuego->jugador->getManaMax()){
                        estadoJuego->jugador->setMana(estadoJuego->jugador->getManaMax());
                        estadoJuego->jugador->info->setMana(estadoJuego->jugador->getManaMax());
                    }
                    else{
                        estadoJuego->jugador->setMana(estadoJuego->jugador->getMana() + objetosTienda[objetoSeleccionado]->getStats().mana);
                        float mana = estadoJuego->jugador->info->sumarMana(objetosTienda[objetoSeleccionado]->getStats().mana);
                    }
                }
            }
        }
        else if(objetosTienda[objetoSeleccionado]->getType() == "Mapa"){
            if(idTienda == 269 || idTienda == 268){
                if(idTienda == 268){
                    estadoJuego->mapaBosque = true;
                }
                else{
                    estadoJuego->mapaMontana = true;
                }
                motor->window.clear(); 
                sprites.clear();
                objetosTienda.clear();
                costeObjetos.clear();
                monedasCoste.clear();
                optionsTienda.clear();
            }
        }
        else{
            estadoJuego->jugador->updateObjetosDisponibles(objetosTienda[objetoSeleccionado]);
        }
        optionsTienda[objetoSeleccionadoPressed()].setString(nombre);

        if(idTienda == 263){
            // Deletes the second element (vec[1]) vec.erase(vec.begin() + 1);
            //oculto el objeto pero no lo borro, habra que verlo
            updateTienda();

        }
   
    }
}


void ShopState::Update(const float &dt){
  
}

void ShopState::updateTienda(){
    motor->window.clear(); 
    sprites.clear();
    objetosTienda.clear();
    costeObjetos.clear();
    monedasCoste.clear();
    optionsTienda.clear();
    Init();

}

void ShopState::Render(const float &dt){


    // para que no se vea nada de fondo
    if(objetosTienda.size() > 0){
        motor->window.clear(); 
        motor->drawSprite(tiendaBG);
        motor->drawSprite(dineroJugador);
        motor->drawText(cantDineroJugador);
        motor->drawText(labelArmadura);
        motor->drawText(labelMana);
        motor->drawText(labelVida);
        motor->drawText(labelDanio);
        motor->drawText(aumentoArmadura);
        motor->drawText(aumentoMana);
        motor->drawText(aumentoVida);
        motor->drawText(aumentoDanio);


        for(int i = 0; i < (int)sprites.size(); i++){
            motor->drawSprite(sprites[i]);
        }
        motor->drawRectangleShape(selector);
        for(unsigned int i = 0; i < objetosTienda.size(); i++){
            motor->drawText(optionsTienda[i]);
        }
        for(unsigned int i = 0; i < costeObjetos.size(); i++){
            motor->drawText(costeObjetos[i]);
        }

        for(unsigned int i = 0; i < monedasCoste.size(); i++){
            motor->drawSprite(monedasCoste[i]);
        }
        motor->window.display();
    }
    else{
        motor->window.clear(); 
        motor->drawSprite(tiendaBG);
        motor->drawText(cantDineroJugador);
        motor->drawSprite(dineroJugador);
        motor->window.display();
    }
        
   
}

void ShopState::moveLeft(){
    if(objetoSeleccionado >= 0 && optionsTienda.size() > 1){

        if (objetoSeleccionado == 0){
            objetoSeleccionado = optionsTienda.size();
        }
        if(optionsTienda[objetoSeleccionado].getString() == "Comprar?"){
            optionsTienda[objetoSeleccionado].setString(nombre);
        }
        selector.setSize(sf::Vector2f(optionsTienda[objetoSeleccionado - 1].getLocalBounds().width,optionsTienda[objetoSeleccionado - 1].getLocalBounds().height + 5.f));
        selector.setPosition(optionsTienda[objetoSeleccionado - 1].getPosition().x,optionsTienda[objetoSeleccionado - 1].getPosition().y);

        if(objetosTienda[objetoSeleccionado - 1]->getStats().armour != 0){
            aumentoArmadura.setString("+"+num2String(objetosTienda[objetoSeleccionado - 1]->getStats().armour));
        }
        else{
            aumentoArmadura.setString("");
        }
        if(objetosTienda[objetoSeleccionado - 1]->getStats().health != 0){
            aumentoVida.setString("+"+num2String(objetosTienda[objetoSeleccionado - 1]->getStats().health));
        }
        else{
            aumentoVida.setString("");
        }
        if(objetosTienda[objetoSeleccionado - 1]->getStats().mana != 0){
            aumentoMana.setString("+"+num2String(objetosTienda[objetoSeleccionado - 1]->getStats().mana));
        }
        else{
            aumentoMana.setString("");
        }
        if(objetosTienda[objetoSeleccionado - 1]->getStats().damage != 0){
            aumentoDanio.setString("+"+num2String(objetosTienda[objetoSeleccionado - 1]->getStats().damage));
        }
        else{
            aumentoDanio.setString("");
        }
        objetoSeleccionado--;
    }
}


void ShopState::moveRight(){
    if(objetoSeleccionado <= optionsTienda.size() && optionsTienda.size() > 1){
        if (objetoSeleccionado == optionsTienda.size()-1){
            objetoSeleccionado = -1;
        }
        if(optionsTienda[objetoSeleccionado].getString() == "Comprar?"){
            optionsTienda[objetoSeleccionado].setString(nombre);
        }
        selector.setSize(sf::Vector2f(optionsTienda[objetoSeleccionado + 1].getLocalBounds().width,optionsTienda[objetoSeleccionado + 1].getLocalBounds().height + 5.f));
        selector.setPosition(optionsTienda[objetoSeleccionado + 1].getPosition().x,optionsTienda[objetoSeleccionado + 1].getPosition().y);
        if(objetosTienda[objetoSeleccionado + 1]->getStats().armour != 0){
            aumentoArmadura.setString("+"+num2String(objetosTienda[objetoSeleccionado + 1]->getStats().armour));
        }
        else{
            aumentoArmadura.setString("");
        }
        if(objetosTienda[objetoSeleccionado + 1]->getStats().health != 0){
            aumentoVida.setString("+"+num2String(objetosTienda[objetoSeleccionado + 1]->getStats().health));
        }
        else{
            aumentoVida.setString("");
        }
        if(objetosTienda[objetoSeleccionado + 1]->getStats().mana != 0){
            aumentoMana.setString("+"+num2String(objetosTienda[objetoSeleccionado + 1]->getStats().mana));
        }
        else{
            aumentoMana.setString("");
        }
        if(objetosTienda[objetoSeleccionado + 1]->getStats().damage != 0){
            aumentoDanio.setString("+"+num2String(objetosTienda[objetoSeleccionado + 1]->getStats().damage));
        }
        else{
            aumentoDanio.setString("");
        }
        objetoSeleccionado++;
    }
}

int ShopState:: objetoSeleccionadoPressed(){
    return objetoSeleccionado;
}

std::string ShopState::num2String(int num){
    std::string m;
    std::ostringstream sm;

    sm << num;
    m = sm.str();

    return m;
}