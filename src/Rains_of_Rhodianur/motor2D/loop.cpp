
#include "loop.h"
#include "../states/initcredits_state.h"


//Constructor por defecto
Loop::Loop(){
  this->init();
  this->loop_game();
}

Loop::~Loop(){
}

void Loop::init(){
  motor = Motor2D::Instance();
  gamedata->states.addState(state_ptr(new InitCreditsState(this->gamedata)));
  this->loop_game();
}

//Bucle principal del juego
void Loop::loop_game(){

  float tiempoFrame = 0.f;

  while(motor->window.isOpen())
  {
    tiempoFrame += this->clock.restart().asSeconds();

    while (tiempoFrame > this->delta)
    {
        tiempoFrame -= this->delta;

        this->gamedata->states.changeState();
        this->gamedata->states.getCurrentState()->HandleInput();
        this->gamedata->states.getCurrentState()->Update(this->delta);
        this->gamedata->states.getCurrentState()->Render(this->delta);

    }
    
  }

}