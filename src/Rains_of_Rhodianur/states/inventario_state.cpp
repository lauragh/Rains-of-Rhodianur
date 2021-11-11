#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cmath>

#include "../states/inventario_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"
#include "../states/control_state.h"
#include "../npcs/object.h"

InventarioState::InventarioState(GameData data): datagame(data){}

void InventarioState::Init(){
   actualizar = false;
   motor = Motor2D::Instance();
   motor->addTexture("Inventario", INVENTARIO_FILEPATH);
    sprite.setTexture(motor->getTexture("Inventario"));
    sprite.setOrigin(0,0);
    sprite.setPosition(motor->view.getCenter().x - 300.f, motor->view.getCenter().y - 300.f);
    sprite.scale(0.50f,0.75f);

    GameState *game = GameState::Instance();

    objetoSeleccionado = 0;

    selector = sf::RectangleShape(sf::Vector2f(70,70));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(2.2);
    selector.setOutlineColor(sf::Color::Red);
    selector.setOrigin(0,0);
    selector.setPosition(sprite.getPosition().x+25,sprite.getPosition().y+60);

    equiped = game->jugador->getObjetosEquipados();

    for (int i = 0; i < (int)equiped.size(); i++)
    {
        equipedSprite.push_back(new sf::Sprite());
        equipedSprite[i]->setTexture(motor->getTexture("sprite_sheet"));
        equipedSprite[i]->setTextureRect(sf::IntRect(equiped[i]->getColumna()* 32, equiped[i]->getFila()* 32, 32, 32));

        if (equiped[i]->getType() == "Casco")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+525,sprite.getPosition().y+115);  
        } else if (equiped[i]->getType() == "Pechera")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+315,sprite.getPosition().y+130);  
        }else if (equiped[i]->getType() == "Principal")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+315,sprite.getPosition().y+245);  
        }else if (equiped[i]->getType() == "Brazos")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+525,sprite.getPosition().y+200);  
        }else if (equiped[i]->getType() == "Piernas")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+525,sprite.getPosition().y+285);  
        }else if (equiped[i]->getType() == "Proyectil")
        {
          equipedSprite[i]->setPosition(sprite.getPosition().x+315,sprite.getPosition().y+345);  
        }
        
    }

    inventario = game->jugador->getObjetosDisponibles();

    for (int i = 0; i < (int)inventario.size(); i++)
    {
        
        inventarioSprite.push_back(new sf::Sprite());
        inventarioSprite[i]->setTexture(motor->getTexture("sprite_sheet"));
        inventarioSprite[i]->setTextureRect(sf::IntRect(inventario[i]->getColumna()* 32, inventario[i]->getFila()* 32, 32, 32));

        if (i<3)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+(i*83)),sprite.getPosition().y+80);   
        } else if (i<6 && i>2)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+((i-3)*83)),sprite.getPosition().y+165);   
        }else if (i<9 && i>5)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+((i-6)*83)),sprite.getPosition().y+250);   
        }else if (i<12 && i>8)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+((i-9)*83)),sprite.getPosition().y+335);   
        }else if (i<15 && i>11)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+((i-12)*83)),sprite.getPosition().y+420);   
        }else if (i<18 && i>14)
        {
            inventarioSprite[i]->setPosition(sprite.getPosition().x+(45+((i-15)*83)),sprite.getPosition().y+505);   
        }
    }

    //Pintar Objetos

    dineroJugador.setTexture(motor->getTexture("sprite_sheet"));
    dineroJugador.setTextureRect(sf::IntRect(10 * 32, 1 * 32, 32, 32));
    dineroJugador.setPosition(sprite.getPosition().x + 280.f, sprite.getPosition().y + 420.f);

    cantDineroJugador = sf::Text();
    cantDineroJugador.setFont(motor->getFont("Dungeon"));
    cantDineroJugador.setCharacterSize(18);
    cantDineroJugador.setString(num2String(game->jugador->getMoney()));
    cantDineroJugador.setPosition(dineroJugador.getPosition().x + 40.f,dineroJugador.getPosition().y + 6.f);
    cantDineroJugador.setStyle(sf::Text::Bold);

    flechasJugador.setTexture(motor->getTexture("sprite_sheet"));
    flechasJugador.setTextureRect(sf::IntRect(11 * 32, 1 * 32, 32, 32));
    flechasJugador.setPosition(sprite.getPosition().x + 280.f, sprite.getPosition().y + 450.f);

    cantFlechasJugador = sf::Text();
    cantFlechasJugador.setFont(motor->getFont("Dungeon"));
    cantFlechasJugador.setCharacterSize(18);
    cantFlechasJugador.setString(num2String(game->jugador->getArrows()));
    cantFlechasJugador.setPosition(flechasJugador.getPosition().x + 40.f,flechasJugador.getPosition().y + 6.f);
    cantFlechasJugador.setStyle(sf::Text::Bold);

    vidaJugador.setTexture(motor->getTexture("sprite_sheet"));
    vidaJugador.setTextureRect(sf::IntRect(8 * 32, 1 * 32, 32, 32));
    vidaJugador.setPosition(sprite.getPosition().x + 280.f, sprite.getPosition().y + 480.f);

    cantVidaJugador = sf::Text();
    cantVidaJugador.setFont(motor->getFont("Dungeon"));
    cantVidaJugador.setCharacterSize(18);
    cantVidaJugador.setString(num2String(game->jugador->getPotiVida()));
    cantVidaJugador.setPosition(vidaJugador.getPosition().x + 40.f,vidaJugador.getPosition().y + 6.f);
    cantVidaJugador.setStyle(sf::Text::Bold);

    manaJugador.setTexture(motor->getTexture("sprite_sheet"));
    manaJugador.setTextureRect(sf::IntRect(9 * 32, 1 * 32, 32, 32));
    manaJugador.setPosition(sprite.getPosition().x + 280.f, sprite.getPosition().y + 510.f);

    cantManaJugador = sf::Text();
    cantManaJugador.setFont(motor->getFont("Dungeon"));
    cantManaJugador.setCharacterSize(18);
    cantManaJugador.setString(num2String(game->jugador->getPotiMana()));
    cantManaJugador.setPosition(manaJugador.getPosition().x + 40.f,manaJugador.getPosition().y + 6.f);
    cantManaJugador.setStyle(sf::Text::Bold);

    //Pintar Stats
    

}

void InventarioState::HandleInput()
    {
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
                    case sf::Keyboard::Right:
                        moveRight();
                        break;

                    case sf::Keyboard::Left:
                        moveLeft();
                        break;

                    case sf::Keyboard::Up:
                        moveUp();
                        break;

                    case sf::Keyboard::Down:
                        moveDown();
                        break;

                    case sf::Keyboard::Return:
                        actualizar = intercambiarObjeto();
                        break;

                    case sf::Keyboard::Escape:
                        //Go to Game Screen
                        datagame->states.popState();
                        break;
                    default:
                        break;
                }
            }
        }
    }

void InventarioState::Update(const float &dt){
   if (actualizar){
        pintar();
        actualizar = false;
    }
}

void InventarioState::Render(const float &dt){

    motor->window.clear();

    motor->drawSprite(sprite);
    for (int i = 0; i < (int)equipedSprite.size(); i++)
    {
        motor->drawSprite(equipedSprite[i]);
    }

    for (int i = 0; i < (int)inventarioSprite.size(); i++)
    {
        motor->drawSprite(inventarioSprite[i]);
    }

    motor->drawSprite(dineroJugador);
    motor->drawText(cantDineroJugador);

    motor->drawSprite(flechasJugador);
    motor->drawText(cantFlechasJugador);

    motor->drawSprite(vidaJugador);
    motor->drawText(cantVidaJugador);

    motor->drawSprite(manaJugador);
    motor->drawText(cantManaJugador);
    
    motor->drawRectangleShape(selector);

    motor->window.display();
}

void InventarioState::moveRight(){
    
    if (objetoSeleccionado == 2 || objetoSeleccionado == 5 || objetoSeleccionado == 8 || objetoSeleccionado == 11 || objetoSeleccionado == 14 || objetoSeleccionado == 17)
    {
        selector.setPosition(selector.getPosition().x - 167, selector.getPosition().y);
        objetoSeleccionado = objetoSeleccionado-2;
    }else{
        selector.setPosition(selector.getPosition().x + 83.5, selector.getPosition().y);
        objetoSeleccionado++;
    }
}

void InventarioState::moveLeft(){
    
    if (objetoSeleccionado == 0 || objetoSeleccionado == 3 || objetoSeleccionado == 6 || objetoSeleccionado == 9 || objetoSeleccionado == 12 || objetoSeleccionado == 15)
    {
        selector.setPosition(selector.getPosition().x + 167, selector.getPosition().y);
        objetoSeleccionado = objetoSeleccionado+2;
    }else{
        selector.setPosition(selector.getPosition().x - 83.5, selector.getPosition().y);
        objetoSeleccionado--;
    }
}

void InventarioState::moveUp(){
    
    if (objetoSeleccionado == 0 || objetoSeleccionado == 1 || objetoSeleccionado == 2)
    {
        selector.setPosition(selector.getPosition().x, selector.getPosition().y + 422.5);
        objetoSeleccionado = objetoSeleccionado+15;
    }else{
        selector.setPosition(selector.getPosition().x, selector.getPosition().y - 84.5);
        objetoSeleccionado = objetoSeleccionado - 3;
    }
}

void InventarioState::moveDown(){
    
    if (objetoSeleccionado == 15 || objetoSeleccionado == 16 || objetoSeleccionado == 17)
    {
        selector.setPosition(selector.getPosition().x, selector.getPosition().y - 422.5);
        objetoSeleccionado = objetoSeleccionado-15;
    }else{
        selector.setPosition(selector.getPosition().x, selector.getPosition().y + 84.5);
        objetoSeleccionado = objetoSeleccionado + 3;
    }
}

bool InventarioState::intercambiarObjeto(){
    Object *aux;
    sf::Sprite *auxSprite;
    GameState *game = GameState::Instance();
    if(objetoSeleccionado>=(int)inventario.size()){
        return false;
    }else{
        if (inventario[objetoSeleccionado]->getType() == "Casco")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[4];
            equiped[4]=aux;

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[4]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[4]->setTextureRect(auxSprite->getTextureRect());

        } else if (inventario[objetoSeleccionado]->getType() == "Pechera")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[5];
            equiped[5]=aux;

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[5]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[5]->setTextureRect(auxSprite->getTextureRect());
        }else if (inventario[objetoSeleccionado]->getType() == "Principal")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[0];
            equiped[0]=aux; 

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[0]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[0]->setTextureRect(auxSprite->getTextureRect());
        }else if (inventario[objetoSeleccionado]->getType() == "Brazos")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[6];
            equiped[6]=aux;

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[6]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[6]->setTextureRect(auxSprite->getTextureRect());
        }else if (inventario[objetoSeleccionado]->getType() == "Piernas")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[7];
            equiped[7]=aux; 

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[7]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[7]->setTextureRect(auxSprite->getTextureRect());
        }else if (inventario[objetoSeleccionado]->getType() == "Proyectil")
        {
            aux = inventario[objetoSeleccionado];
            inventario[objetoSeleccionado] = equiped[1];
            equiped[1]=aux;

            auxSprite = new sf::Sprite(*inventarioSprite[objetoSeleccionado]);
            //inventarioSprite[objetoSeleccionado] = equipedSprite[4];
            inventarioSprite[objetoSeleccionado]->setTextureRect(equipedSprite[1]->getTextureRect());  
            //equipedSprite[4] = auxSprite;
            equipedSprite[1]->setTextureRect(auxSprite->getTextureRect());

            game->jugador->ataqueSecundarioSelected = equiped[1]->getName();
             
        }else{
            return false;
        }
        
        game->jugador->equiped = equiped;
        game->jugador->available = inventario;
        game->jugador->t_health=100;
        game->jugador->t_mana=100;
        for(int i=0;i<(int)game->jugador->equiped.size();i++){
            Object *aux=game->jugador->equiped[i];
            game->jugador->t_health=game->jugador->t_health+aux->getStats().health;
            game->jugador->t_mana=game->jugador->t_mana+aux->getStats().mana;
        }
        if(game->jugador->t_health < game->jugador->health){
            game->jugador->health=game->jugador->t_health;
        }
        if(game->jugador->t_mana < game->jugador->mana){
            game->jugador->mana=game->jugador->t_mana;
        }
        game->jugador->armadura=0;
        for(int i=0;i<(int)game->jugador->equiped.size();i++){
            Object *aux=game->jugador->equiped[i];
            game->jugador->armadura=game->jugador->armadura+aux->getStats().armour;
        }



        return true;
    }
}

void InventarioState::pintar(){
    motor->window.clear();

    motor->drawSprite(sprite);
    for (int i = 0; i < (int)equipedSprite.size(); i++)
    {
        motor->drawSprite(equipedSprite[i]);
    }

    for (int i = 0; i < (int)inventarioSprite.size(); i++)
    {
        motor->drawSprite(inventarioSprite[i]);
    }
    
    motor->drawRectangleShape(selector);

    motor->window.display();
}

std::string InventarioState::num2String(int num){
    std::string m;
    std::ostringstream sm;

    sm << num;
    m = sm.str();

    return m;
}