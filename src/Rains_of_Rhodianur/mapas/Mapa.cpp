#include "Mapa.h"
Mapa:: Mapa(){
    motor = Motor2D::Instance();
}


Mapa::~Mapa(){
    for(int l=0;l<numCapas;l++){
    for(int y=0;y<alto;y++){
      delete[] tileArray[l][y];
    }
    delete[] tileArray[l];
  }

  delete[] tileArray;
  tileArray = NULL;

  //Elimino la matriz de gids
    for(int y=0;y<alto;y++){
        delete[] gitMatrix[y];
    }
  gitMatrix = NULL;
}
//Obtenemos los datos del TMX y los guardamos. El path es la ruta del .tmx
void Mapa::cargarMapaTMX(const char* path){

    rellenartilesdanyinos();

    XMLDocument doc;

    doc.LoadFile(path);
    
    //Obtenemos las dimensiones del mapa y de los tiles
    XMLElement* map = doc.FirstChildElement("map");
    map->QueryIntAttribute("width",&ancho);
    map->QueryIntAttribute("height",&alto);
    map->QueryIntAttribute("tilewidth",&anchoTile);
    map->QueryIntAttribute("tileheight",&altoTile);


    //Cargamos la imagen que usamos en el tileset
    const char* resource = "resources/";    
    std::string ruta (resource);
    XMLElement* img = map->FirstChildElement("tileset")->FirstChildElement("image");
    const char* filename = img->Attribute("source");
    ruta.append(filename);
    tile.loadFromFile(ruta);

    //Buscamos ahora todas las capas de las que se forma nuestro mapa. Nostros sabemos que tiene 3, al menos de momento
    numCapas = 0;
    XMLElement* layer = map->FirstChildElement("layer");
    while(layer){
        numCapas++;
        layer=layer->NextSiblingElement("layer");
    }

    //Creamos la matriz 3D donde guargamos los tiles (sus IDs?)
    tileArray = new int**[numCapas];
    for(int i = 0; i < numCapas;i++){
        tileArray[i] = new int* [alto]; //alto
    }
    for(int i = 0;i < numCapas; i++){
        for(int j = 0; j < alto;j++){//alto
            tileArray[i][j] = new int[ancho]; //ancho
        }
    }
    //Ya de paso, vamos a recorrer toda la matriz para rellenarla de 0
    for(int i = 0; i < numCapas; i++){
        for(int j = 0; j < alto;j++){//alto
            for(int k = 0; k < ancho; k++){//ancho
                tileArray[i][j][k] = 0;
            }
        }
    }

    //Aprovechamos para crear la matriz que podremos usar para calcular las colisiones. Se hará de la misma manera que la anterior
    //Esta es solo de 2 dimensiones porque solo calculamos colisiones con una de las capas, no con las 3
    gitMatrix = new int*[alto]; //alto

    for(int i = 0; i < alto; i++) //alto
        gitMatrix[i] = new int [ancho]; //ancho

    for(int i = 0; i<alto; i++){ //alto
        for(int j=0;j<ancho;j++){//ancho
            gitMatrix[i][j] = 0;
        }
    }

    /*
    posiciones = new sf::Vector2f*[alto];
    for(int i = 0; i < alto; i++)
       posiciones[i] = new sf::Vector2f[ancho];
       
    */

    //Vamos a cargar los GID en la matrix
    //Esta matriz de 3 dimensiones funciona así: capa-ancho-alto, y la recorreremos entera guardando en cada celda su GID correspondiente
    //Primera capa
    this->data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    int contador = 1;
    int comprobar = 0;
    for(int i = 0; i < numCapas; i++){
        for(int j = 0; j < alto;j++){ //alto
            for(int k = 0; k < ancho; k++){//ancho
                //Aqui puede explotar, porque hay muchos tiles vacios, y no se si el metodo queryIntAttribute devolvera un numero de error o un mensaje
                data->QueryIntAttribute("gid",&comprobar);
                if(comprobar != 0){
                    //Asumiendo que lo anterior este bien, guardaremos el gid correspondiente en su casilla de la matriz aaababa
                    data->QueryIntAttribute("gid",&tileArray[i][j][k]);
                    if(i == 2){//La capa principal
                        data->QueryIntAttribute("gid",&gitMatrix[j][k]);
                        if(gitMatrix[j][k] != 0){
                            gitMatrix[j][k] = gitMatrix[j][k]-1;
                        }
                        
                    }
                    
                }
                //Avanzamos al siguiente tile
                this->data = data->NextSiblingElement("tile");
            }
        }
        //Avanzamos a la capa siguiente
        //Mira, esto es sucio,esta mal, pero fuck it, yo se que no vamos a hacer más de 3 capas  de profundidad
        if(contador == 1){//Acabamos de recorrer la primera capa (fondo trasero), queremos acceder al fondo intermedio
            this->data = map->FirstChildElement("layer")->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }else if(contador == 2){//Acabamos de recorrer la segunda capa (fondo intermedio), queremos acceder a la capa principal
            this->data = map->FirstChildElement("layer")->NextSiblingElement("layer")->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }else if(contador == 3){//Acabamos de recorrer la capa de fondo intermedio, y queremos recorrer la tercera capa
            this->data = map->FirstChildElement("layer")->NextSiblingElement("layer")->NextSiblingElement("layer")->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        }
        contador++;
    }

    //Ahora leeremos la posicion de los enemigos y nos guardaremos su posición y tipo
    //En el tiled la coordenada x e y de los objetos representa el punto de arriba a la izquierda
    XMLElement* objeto = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    while(objeto){
        //IMPORTANTE, si desplazas el mapa, también debes de desplazar la posición de los enemigos
        const char* nombre = objeto->Attribute("name");
        
        if(strcmp(nombre,"Enemigo")==0){
            //Pillamos el tipo que es y su posicion, hacemos una estructura y lo almacenamos en el vector
            const char* type = objeto->Attribute("type");
            
            int tipo = atoi(type);
            
            const char *x = objeto->Attribute("x");
            const char *y = objeto->Attribute("y");
            int x2 = atoi(x);//Convierte un string en int
            int y2 = atoi(y);
            
            sf::Vector2f pos = sf::Vector2f(x2, y2);
            struct enemyDat enemigoData = {tipo,pos};
            enemigos.push_back(enemigoData);
        }//Puntos de spawn, al cambiar entre mapas o al morir
        else if(strcmp(nombre,"Respawn")==0){
            //Recuerda que el vector que te guardas es la posición del punto de arriba a la izquierda del cuadrado
            const char* type = objeto->Attribute("type");
            int identificador = atoi(type);
            
            const char *x = objeto->Attribute("x");
            const char *y = objeto->Attribute("y");
            int x2 = atoi(x);
            int y2 = atoi(y);
            sf::Vector2f pos = sf::Vector2f(x2, y2);
            struct spawnDat spawnData = {identificador,pos};
            spawns.push_back(spawnData);
        }//Monedas,puertas, interruptores
        else if(strcmp(nombre,"Objeto") == 0 || strcmp(nombre,"Puerta") == 0 ||strcmp(nombre,"Interruptor") == 0){

        }

        //Avanzo al siguiente objeto
        objeto = objeto ->NextSiblingElement("object");
    }
}

//Escucha no te vas a morir por poner una comprobación de vez en cuando jefe
//Este método lee las matrices que hemos leído del .tmx y crea los quads asignándoles su sprite correspondiente
bool Mapa::load(sf::Vector2u tile_size, int*** nivel,unsigned int ancho,int numCapas/*,int numNivel*/){
    //https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1VertexArray.php
    //Resize the vertex array to fit the level size
    layer_fondo.setPrimitiveType(sf::Quads);
    layer_fondo.resize(ancho*alto*4);

    layer_intermedio.setPrimitiveType(sf::Quads);
    layer_intermedio.resize(ancho*alto*4);

    layer_normal.setPrimitiveType(sf::Quads);
    layer_normal.resize(ancho*alto*4);

    layer_frontal.setPrimitiveType(sf::Quads);
    layer_frontal.resize(ancho*alto*4);

    //Recorremos la matriz que tenemos de los gits, colocamos los quads en su posición y le damos la textura correspondiente
    for(int k = 0; k < numCapas; k++){
        for(unsigned int i = 0; i < ancho; i++){ //ancho
            for(int j = 0; j < alto; j++){      //alto
                int gid = nivel[k][j][i];

                if(gid>0){
                    gid = gid-1;

                    //Find its position in the tileset texture
                    int tu = gid % (tile.getSize().x/tile_size.x);
                    int tv = gid / (tile.getSize().x/tile_size.x);

                    //Get a pointer to the current tile's quad
                    sf::Vertex* quad;
                    //Comprobamos en que capa estamos, con la variable k del for
                    if(k == 0){//Fondo trasero
                        quad = &layer_fondo[(i+j*ancho)*4];
                    }else if(k == 1){//Fondo intermedio
                        quad = &layer_intermedio[(i+j*ancho)*4];
                    }else if(k == 2){//Capa principal
                        quad = &layer_normal[(i+j*ancho)*4];
                    }else{//Fondo delantero, k == 3
                        quad = &layer_frontal[(i+j*ancho)*4];
                    }

                    //Define its 4 corners
                    quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
                    quad[1].position = sf::Vector2f((i+1)*tile_size.x, j*tile_size.y);
                    quad[2].position = sf::Vector2f((i+1)*tile_size.x, (j+1)*tile_size.y);
                    quad[3].position = sf::Vector2f(i*tile_size.x,(j+1)*tile_size.y);

                    //Define its 4 texture coordinates
                    quad[0].texCoords = sf::Vector2f(tu*tile_size.x, tv*tile_size.y);
                    quad[1].texCoords = sf::Vector2f((tu+1)*tile_size.x, tv*tile_size.y);
                    quad[2].texCoords = sf::Vector2f((tu+1)*tile_size.x, (tv+1)*tile_size.y);
                    quad[3].texCoords = sf::Vector2f(tu*tile_size.x,(tv+1)*tile_size.y);

                }
            }
        }
    }
    
    return true;
}

void Mapa::eliminarMapa(){
  //Elimino la matriz de tiles, creo que se hace así
  
  
}

void Mapa::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    states.texture = &tile;
    //Hacer esto bien para poder manejar el motor multicapa
    //Dibujar la capa frontal depués del personaje
    target.draw(layer_fondo,states);
    target.draw(layer_intermedio,states);
    target.draw(layer_normal,states);    
}

//Falta drawable del mapa
void Mapa::drawMap(){
    //Hacer esto bien para poder manejar el motor multicapa
    //Dibujar la capa frontal depués del personaje
    
    motor->drawMap2(layer_fondo,&tile);
    motor->drawMap2(layer_intermedio,&tile);
    motor->drawMap2(layer_normal,&tile);    
}

void Mapa::draw2(){
    motor->drawMap2(layer_frontal, &tile);
}

//Por aqui hay que liberar memoria de las matrices, que no se nos pase


void Mapa::rellenartilesdanyinos(){

    tilesdanyinos.push_back(3343);
    tilesdanyinos.push_back(2834);
    tilesdanyinos.push_back(2835);
    tilesdanyinos.push_back(8689);
    tilesdanyinos.push_back(8690);
    tilesdanyinos.push_back(8691);
    tilesdanyinos.push_back(3592);
    tilesdanyinos.push_back(3594);
    tilesdanyinos.push_back(3595);
    tilesdanyinos.push_back(4362);
    tilesdanyinos.push_back(4363);
    tilesdanyinos.push_back(4364);
    tilesdanyinos.push_back(4365);
    tilesdanyinos.push_back(4612);
    tilesdanyinos.push_back(4613);
    tilesdanyinos.push_back(4614);
    tilesdanyinos.push_back(4615);
    tilesdanyinos.push_back(10448);
    tilesdanyinos.push_back(10449);
    tilesdanyinos.push_back(10450);
    tilesdanyinos.push_back(10451);
    tilesdanyinos.push_back(10452);
    tilesdanyinos.push_back(10453);

}