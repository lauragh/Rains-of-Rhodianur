#include <SFML/Graphics.hpp>
#include <iostream>

#include "motor2D/loop.h"

#include "include/config.h"


int main() {


  Loop *bucle_juego = new Loop();

  bucle_juego->loop_game();

  return 0;
}