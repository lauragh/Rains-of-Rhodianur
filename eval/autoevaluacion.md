# Autoevaluación individual

## Antonio David Ortiz Peral

    Se ha implementado una IA del tipo patrulla, esta se mueve aumentando su velocidad hasta cierto punto y luego invierte el sentido.
    No se han encontrado problemas a la hora de desarrollar el prototipo pero este tipo de IA funcionará diferente en el futuro ya que tomará como referencia de movimiento 2 puntos en el mapa.

## Àngel Torregrosa Calabuig

    Se ha implementado un menú principal y diferentes estados por los cuales navegar.
    El único problema que he tenido ha sido el error con un puntero a la hora de reanudar la partida estando en el estado de menú de pausa y el cual no he podido solucionar.

## Alfredo Pérez Pinedo

    He implementado el mapa leyéndolo desde un fichero tmx y dibujándolo por capas, una de ellas se dibuja por delante del jugador, con lo que lo tapa si pasa por ahí.
    No se han encontrado demasiados problemas a la hora de leer el fichero, colocar y dibujar los sprites, pero no están implementadas las colisiones con el mapa. Eh encontrado dos formas de hacerlo: Basado en grids o en quad tree.

## Laura García Hernández

    Se ha implementado el hud del juego, sprites para iconos y shapes (texto y rectángulos). No he encontrado problemas significantes, pero no he aplicado tiempo de reloj para este hito.

## Alba Ruiz Maiques

    Se ha implementado el movimiento básico del personaje, tratando este el movimiento lateral, agacharse(en proceso de mejora por tener que encontrar una forma de reducir la hitbox en este estado) y salto con gravedad. También, se han implementado colisiones y animaciones acordes al movimiento que realice el personaje.


# Autoevaluación general

    Hito 1

    Responsables de los prototipos:

        - Alba -> Movimiento_basico
        - Àngel -> menus
        - Alfredo -> mapas
        - Laura -> interfaz
        - Antonio -> enemyIA1

Nota propuesta del Hito 1: 8 global










## ------------- HITO 2 -------------
# Autoevaluación individual

## Antonio David Ortiz Peral

    Se ha implementado la clase zonas.h/zonas.cpp que contiene y gestiona toda la información de cada fragmento de mapa.
    Se ha implementado la clase enemy.h/enemy.cpp que contiene la información relativa a los tipos de enemigos, así como su creación y sus colisiones.
    Se ha actualizado player.h/player.cpp con colisiones con el mapa y con los enemigos.
    Se han arreglado errores varios de otras clases así como de estructura.

    Se han encontrado problemas durante el desarrollo pero se han solucionado la mayoría de ellos. Actualmente se está trabajando con las colisiones del jugador con las paredes dado que se han encontrado errores que no encuentro como resolver.

## Àngel Torregrosa Calabuig

    Se ha implementado el manejador de estados, con la gestión de los estados.
    Se ha implementado la clase estado de la animación principal, donde se muestra el logo del grupo.
    Se ha implementado la clase estado menú principal, que desde este tenemos acceso al estado juego.
    Se ha implementado la clase estado menu de pausa, la cual se puede acceder desde el estado juego con la tecla ESC.
    Se ha implementado la clase objetos, esta clase lee de un fichero todas las stats de los objetos que dispondra el jugador y los carga en el estado de juego.
    Se ha implementado la clase proyectil, esta dispone de colisiones con el mapa y enemigos.

    Se han realizado las animaciones del ataque principal y ataque secundario del jugador.

    Se ha modificado la clase Motor2D para que sea Singleton pero no se ha subido por error en una clase.

    Se han encontrado problemas que se han podido solucionar con la ayuda de los compañeros, salvo el error comentado anteriormente.


## Alfredo Pérez Pinedo
    Se ha continuado con la clase mapa, consiguiendo 4 capas de dibujado y gestionando las posiciones de enemigos, monedas, puertas y checkpoints. He dedicado el resto del tiempo a diseñar los mapas en Tiled.

    No hubo muchos problemas relacionados con el desarrollo.

Se ha continuado con la clase mapa, consiguiendo 4 capas de dibujado y gestionando las posiciones de enemigos, monedas, puertas y checkpoints. He dedicado el resto del tiempo a diseñar los mapas en Tiled.

## Laura García Hernández
    Se ha implementado la clase interfaz.h y interfaz.cpp y contiene la información del personaje plasmada en el hud

    Los pequeños problemas encontrados se han solucionado menos uno que tendré que arreglar para el próximo hito


## Alba Ruiz Maiques
    Se ha implementado la clase player.h/player.cpp con la estructura general y animaciones al personaje acordes al movimiento.

    Se han encontrado problemas pero la mayoría se han ido solucionando a lo largo del desarroyo del proyecto

# Autoevaluación general

    Hito 2

    Porcentaje de trabajo por integrante:

        - Alba      ->  20%
        - Àngel     ->  20%
        - Alfredo   ->  20%
        - Laura     ->  20%
        - Antonio   ->  20%

Nota propuesta del Hito 2: 6 global


## ------------- HITO 3 -------------
# Autoevaluación individual

## Antonio David Ortiz Peral

    Se han solucionado numerosos errores con las colisiones del jugador
    Se ha implementado la mecanica del salto escalada
    Se ha implementado la mecanica del dash
    Se ha implementado un modo debug
    Se ha implementado un modo dios
    Se ha implementado colisiones con tiles danyinos del mapa
    Se ha implementado colision con proyectiles enemigos
    Se han implementado arreglos varios en el funcionamiento de los proyectiles
    Se han ajustado todas las cajas de colision
    Se ha implementado el ataque basico
    Se han implementado 9 patrones de IA de enemigos -> consultar el Ten Sheet para ver que hace cada una de ellas
    
    Se han realizado labores de mejora de rendimiento y arreglos en numerosas clases


## Àngel Torregrosa Calabuig

    Se ha arreglado el error de la clase Motor2D para que sea Singleton, que no se pudo solucionar para el hito anterior.
    Se ha ayudado en la implementación de la cámara que sigue al jugador y con la música.
    Se ha implementado el cambio de zona entre los distintos mapas.
    Se ha implementado un estado de Game over, el cual podrá reiniciar desde el último checkpoint o ir al menú principal.
    Se ha seteado la posición de los menús en función a la posición del jugador.
    Se ha creado un estado Tienda, que luego ha sido desarrollado por Laura.
    Se ha implementado el lanzamiento del proyectil de los enemigos junto a Antonio.
    Se ha realizado el menu de las opciones donde se accede a los controles y a las opciones de desactivar el sonido.
    Se ha creado un estado donde se muestran los diferentes controles del juego.
    Se ha creado el estado mapa donde se muestra el mapa si lo has comprado anteriormente en la tienda o un texto en su defecto.
    Se ha creado el estado Inventario donde se muestran los objetos que tienes disponibles y poder cambiarlos. También se muestran las potis, la cantidad de monedas y flechas disponibles.
    Se ha añadido un reloj para controlar el spam del dash.
    Se ha añadido la suma de monedas al eliminar un enemigo.
    Se ha realizado la funcionalidad del checkpoint junto con Antonio.
    

    Se han encontrado problemas que se han podido solucionar con la ayuda de los compañeros, salvo el error comentado anteriormente.

## Alfredo Pérez Pinedo
    Se han diseñado nuevas zonas: montaña, salas de jefe de ambas zonas.
    Se ha preparado el soporte en el mapa para las funcionalidades de checkpoint, cambios de zona, carga de enemigos, comportamiento de algunas IA, daño de entorno.
    Se han buscado spritesheets de enemigos varios.
    Se han arreglado varios menores relacionados con la tienda de mapas, consumo de pociones y gasto de mana.

    Los problemas encontrados se han solucionado gracias a la ayuda de mis compañeros.




## Laura García Hernández
    Se han buscado canciones
    Se ha implementado la musica del juego
    Se han solucionado errores de la interfaz
    Se han solucionado errores de la camara
    Se ha implementado las tiendas del juego, que en total son 5 junto con sus funcionalidades y updates del jugador al usar la tienda
    Se ha implementado la visualización de la barra de los enemigos
    Se ha modificado el sprite sheet 
    Se han añadido objetos


## Alba Ruiz Maiques
    Se ha implementado el ataque principal del jugador.
    Se ha implementado el cambio de ataques secundarios del jugador.
    Se ha implementado el sistema de daño del juego, tanto del jugador como de los enemigos.
    Se ha implementado la muerte del jugador.
    Se han realizado las animaciones de los enemigos.
    Se ha implementado el consumo de pociones y gasto de maná.
    Se han implementado destructores de las clases más exigentes en cuanto a memoria.
    Se ha gestionado el cambio de stats del jugador al equiparse distintos objetos.

# Autoevaluación general

    Hito 3

    Porcentaje de trabajo por integrante:

        - Alba      ->  20%
        - Àngel     ->  20%
        - Alfredo   ->  20%
        - Laura     ->  20%
        - Antonio   ->  20%

Nota propuesta del Hito 3: 8 global
