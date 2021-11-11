
#include "../states/game_state.h"


GameState* GameState::pinstance = 0;
GameState* GameState::Instance(GameData data){

    if(pinstance == 0){

        pinstance = new GameState(data);
    }

    return pinstance;
}

GameState* GameState::Instance(){

    return pinstance;
}

GameState::GameState(){}

GameState::GameState(GameData data): datagame(data){
    
}

void GameState::Init(){
    
    motor = Motor2D::Instance();
    //Se crean los objetos

    readTxtandLoadObjects();
    relojProyectil = new sf::Clock;
    relojDisparo = new sf::Clock;

    mapaBosque = false;
    mapaMontana = false;
    
    zonactual = new zonas();
    zonactual->crearZona(1);
    
    jugador= new player(sf::Vector2u(6,22),0.1f,100.0f,50.0f, zonactual->mapactual->spawns[0].posicion.x, zonactual->mapactual->spawns[0].posicion.y);
    musicaActiva = true;
    
    std::string nombre;
    nombre = "Call_of_the_Wind.wav";
    if (music.openFromFile("./resources/canciones/"+nombre)){
        
        if(musicaActiva){
            music.play();
        }
        music.setLoop(true);
    }
    else{
       std::cerr << "Error cargando la cancion"+nombre; 
    }

}

void GameState::HandleInput(){
    sf::Event event;

    while (motor->window.pollEvent(event))
    {
        switch (event.type) {

            //Si se recibe el evento de cerrar la ventana la cierro
            case sf::Event::Closed:
                motor->window.close();
                break;

            //Se pulsó una tecla, imprimo su codigo
            case sf::Event::KeyPressed:

                //Verifico si se pulsa alguna tecla de movimiento
                switch (event.key.code) {

                    //Tecla ESC menu de pausa
                    case sf::Keyboard::Escape:
                        datagame->states.addState(state_ptr(new PauseMenuState(this->datagame)),false);
                        break;

                    case sf::Keyboard::F12:

                        if(!motor->debug){
                            motor->debug = true;
                        }else {
                            motor->debug = false;
                        }

                        break;

                    case sf::Keyboard::F11:

                        if(!motor->godmode){
                            motor->godmode = true;
                        }else {
                            motor->godmode = false;
                        }

                        break;

                    case sf::Keyboard::F10:

                        this->jugador->money= this->jugador->money+1000;

                        break;

                    case sf::Keyboard::F1:

                        if(!this->jugador->saltoEscalada){
                            this->jugador->saltoEscalada = true;
                        } else {
                            this->jugador->saltoEscalada = false;
                        }

                        if(!this->jugador->dash){
                            this->jugador->dash = true;
                        } else {
                            this->jugador->dash = false;
                        }
                        break;

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){


    }

                    //Cualquier tecla desconocida se imprime por pantalla su código
                    default:
                        break;
                }

            default:
                break;
        }
    }
}

void GameState::Update(const float &dt){

    for(int i=0; i< (int)zonactual->enemylist.size(); i++){

        zonactual->enemylist[i]->Update(dt);
    }
    jugador->Update(dt);

    //Disparar
    if(jugador->getDisparo() && relojDisparo->getElapsedTime().asSeconds() >= 1){
        relojDisparo->restart();
        std::string direccion = "";
        if (jugador->getFace())
        {
            direccion = "derecha";
        }else{
            direccion = "izquierda";
        }
        
        proyectil= new Proyectil(jugador->getTipoDisparo(), jugador->GetPosition(), jugador->getFace(), direccion,1);
        proyectilesLanzados.push_back(proyectil);
    }
    //Posicion de los proyectiles
    if(relojProyectil->getElapsedTime().asMilliseconds() >= 10){
        relojProyectil->restart();
        for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
            proyectilesLanzados[i]->UpdatePos(dt);
            if(proyectilesLanzados[i]->getColision()){
                delete proyectilesLanzados[i];
                proyectilesLanzados.erase(proyectilesLanzados.begin() + i);
            }
        }
    }
    
}

void GameState::Render(const float &dt){

    motor->window.clear();

    zonactual->mapactual->drawMap();

    

    //Pintar los enemigos
    for(unsigned int i=0; i<zonactual->enemylist.size(); i++){
        zonactual->enemylist[i]->draw();
    }
    jugador->Draw();

    //Pintar los proyectiles lanzados
    for(unsigned i = 0; i < proyectilesLanzados.size(); i++){
      proyectilesLanzados[i]->Draw();
    }

    zonactual->mapactual->draw2();

    jugador->info->draw();

    //datagame->window.draw(_background);
    //hud->draw(datagame->window);
    motor->window.display();
}

void GameState::readTxtandLoadObjects(){
    std::string linea;
    bool bought;
    std::vector<std::string> statsObjeto;
    std::ifstream lectura("./resources/objects.txt");

    getline(lectura,linea);
    
    while (getline(lectura,linea))
    {
        statsObjeto = split(linea,';');

        if(statsObjeto[8] == "0"){
            bought = false;
        }else{
            bought = true;
        }

        Object *objeto = new Object(statsObjeto[0], statsObjeto[1], std::stof(statsObjeto[2]), std::stof(statsObjeto[3]), std::stof(statsObjeto[4]), std::stoi(statsObjeto[5]), std::stof(statsObjeto[6]), std::stoi(statsObjeto[7]),bought, statsObjeto[9], std::stoi(statsObjeto[10]), std::stoi(statsObjeto[11]));

        datagame->objects[statsObjeto[0]] = objeto;
    }

    lectura.close();
    
}


std::vector<std::string> GameState::split(std::string separar, char separador) {
	int inicio = 0, encontrado = 0;
	std::string subcadena;
	std::vector<std::string> elems;

	while(encontrado >= 0) {
		encontrado = separar.find(separador, inicio);
		subcadena = separar.substr(inicio, encontrado-inicio);
		inicio = encontrado+1;
		elems.push_back(subcadena);
	}
	return elems;
}

void GameState::cambioZona(int zona, int id_respawn){
    if(zona == 1){
        cambioCancion("Call_of_the_Wind.wav");
    }
    if(zona == 2){
        cambioCancion("Alone_and_Lost.wav");
    }
    else if(zona == 3){
        cambioCancion("Freeze_Frame.wav");
    }
    else if(zona == 4){
        cambioCancion("Dung_Defender.wav");
    }
    else if(zona == 5){
        cambioCancion("False_Knight.wav");
    }
    delete zonactual->mapactual;
    zonactual->crearZona(zona);
    jugador->setPositionRespawn(id_respawn);
    jugador->info->setView(jugador->GetPosition().x, jugador->GetPosition().y);

}

void GameState::reaparecerCheckpoint(){
    int zona, id_respawn;
    if(jugador->respawn == 500){
        zona = 2;
        id_respawn = 6;
    }else if(jugador->respawn == 501){
        zona = 2;
        id_respawn = 7;
    }else if(jugador->respawn == 502){
        zona = 2;
        id_respawn = 8;
    }else if(jugador->respawn == 503){
        zona = 2;
        id_respawn = 9;
    }else if(jugador->respawn == 504){
        zona = 3;
        id_respawn = 4;
    }else if(jugador->respawn == 505){
        zona = 3;
        id_respawn = 5;
    }else if(jugador->respawn == 506){
        zona = 3;
        id_respawn = 6;
    }else if(jugador->respawn == 507){
        zona = 3;
        id_respawn = 7;
    }else{
        zona = 1;
        id_respawn = 1;
    }
    
    jugador->health = jugador->t_health;
    jugador->death = false;

    delete zonactual->mapactual;
    zonactual->crearZona(zona);
    jugador->setPositionRespawn(id_respawn);
    jugador->info->setView(jugador->GetPosition().x, jugador->GetPosition().y);
    jugador->info->sumarVida(jugador->health);
    datagame->states.popState();

}

void GameState::cambioCancion(std::string nombre){
    for(int i = 100; i > 0; i--){
        music.setVolume(i);
    }
    music.stop();

    if (music.openFromFile("./resources/canciones/"+nombre)){
        
        if(musicaActiva){
            music.play();
        }
        for(int i = 0; i < 100; i++){
            music.setVolume(i);
        }
        music.setLoop(true);
    }
    else{
       std::cerr << "Error cargando la cancion"+nombre; 
    }
}