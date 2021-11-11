#include <sstream>
#include <iostream>

#include "../states/map_state.h"
#include "../states/mainmenu_state.h"
#include "../states/game_state.h"

MapState::MapState(GameData data,int zona, bool comprado): datagame(data){
    zonaMapa = zona;
    estaComprado = comprado;
}

void MapState::Init(){
    motor = Motor2D::Instance();
    motor->addTexture("Mapa_Bosque", MAPA_BOSQUE_FILEPATH);
    motor->addTexture("Mapa_Montana", MAPA_MONTANA_FILEPATH);
    motor->addTexture("No_Mapa", NO_MAPA_FILEPATH);
    
    sprite.setOrigin(0,0);

    if(zonaMapa == 2 && estaComprado){
        sprite.setTexture(motor->getTexture("Mapa_Bosque"));
    }else if(zonaMapa == 3 && estaComprado){
        sprite.setTexture(motor->getTexture("Mapa_Montana"));
    }else{
        //No dispones de mapa
        sprite.setTexture(motor->getTexture("No_Mapa"));
    }

    sprite.setPosition(motor->view.getCenter().x - 355.f, motor->view.getCenter().y - 300.f);
    sprite.scale(0.55f,0.85f);
}

void MapState::HandleInput()
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
                    case sf::Keyboard::Escape:
                        datagame->states.popState();
                        break;
                }
            }
        }
    }

void MapState::Update(const float &dt){
   
}

void MapState::Render(const float &dt){

    motor->window.clear();

    motor->drawSprite(sprite);

    motor->window.display();
}