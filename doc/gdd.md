# Rains of Rhodianur - Ten Sheet 


-Bugisoft team-
- Alba Ruiz Maiques
- Àngel Torregrosa Calabuig
- Alfredo Pérez Pinedo
- Laura García Hernández
- Antonio David Ortiz Peral


1. **Ficha del juego**

	1.1	Título del juego

	Rains of Rhodianur
    
	1.2	Sistema de juego

    El juego está basado en el subgénero de acción-aventura conocido como Metroidvania y además contará con un fuerte componente RPG.El jugador deberá explorar un mapa considerable divido en 3 áreas interconectadas entre sí. Para poder superar estas zonas el jugador contará con una serie de movimientos como el salto que le permitirá atravesarlas, sin embargo, habrá obstáculos que requieran de habilidades extra que el jugador deberá desbloquear mediante la exploración y el combate. Además, podrá adquirir equipamiento que le otorgará distintas mejoras como vida extra o maná máximo. Cada zona contendrá distintos enemigos, así como un jefe final de zona que al derrotarlo otorgará una habilidad nueva al jugador.
    
	1.3	Público al que va dirigido

   El principal público al que va dirigido es a todas aquellas personas que les gusten los juegos de plataformas y exploración con un combate divertido y desafiante, así mismo a los que buscan un juego con toques RPG y con estética medieval. 
   El juego quedaría clasificado como PEGI 7.
	
	1.4	Resumen de la historia del juego (orientado a la jugabilidad)

   El jugador tomará el control de un campesino cuya aldea acaba de ser atacada por unos magos de un reino lejano que han provocado un diluvio sobre tu tierra y han destrozado tus cultivos. Al no quedar nada a lo que aferrarte decides embarcarte en viaje para derrotar a los magos y restaurar tu aldea. Deberás hacer frente a numerosos desafíos a lo largo de todo el reino para descubrir el paradero de los magos y recuperar tu granja.
	
	1.5	Modos de juego

    -	Modo Historia: modo principal del juego en el que el usuario se adentra en la aventura completa de nuestro protagonista.
    -	Boss Rush: el jugador se enfrentará a los 4 jefes principales del juego de forma consecutiva en un único escenario. Esta funcionalidad se plantea implementarse en un futuro.
	
	1.6	Puntos únicos de nuestro juego

	- Mezcla de metroidvania clásico con toques RPG.
    
	- Mapeado único con 5 zonas totalmente diferenciadas tanto en su estética como en los obstáculos y enemigos a los que te enfrentas.
    
	- 2 jefes con mecánicas únicas y distintas entre ellos.

	1.7	Juegos similares

	- Hollow Knight.

	- Castlevania: Symphony of the Night.

	- Super Metroid
 
2.	**Ámbito y rejugabilidad**

	2.1 Jugabilidad

	2.1.1	Cómo se progresa en el juego

       Para avanzar en el juego la exploración es clave. El jugador encontrará rutas y caminos por los que no podrá continuar de momento, por lo que deberá volver atrás y explorar por otra ruta. Conforme avance, el jugador encontrará maneras de superar dichos obstáculos, ya sea por caminos alternativos o encontrando power-ups que mejoren la movilidad del personaje. Además, el personaje contará con una serie de stats o atributos que podrá aumentar mediante equipamiento que podrás equipar tras comprar en la tienda con el dinero obtenido de derrotar monstruos.
       
	2.1.2	Misiones y estructuras de retos

    El juego presenta una única misión que es derrotar al jefe final. Para ello planteamos una serie de retos al jugador que son en esencia la exploración y el derrotar a varios subjefes que permitirán la entrada a la última zona, donde se encontrará dicho jefe final. 
    Una vez terminado el modo historia por primera vez se desbloqueara un modo Boss Rush, en el cual el jugador se enfrentará a los jefes del juego de forma continua.
    
	2.1.3	Objetivos del juego

    El objetivo principal del juego es atravesar las distintas zonas y derrotar a los jefes que allí se encuentran para poder acceder a la zona final donde nos esperará el último de los jefes.
    
	2.2	Cuantificación

	2.2.1	Lugares en los que se desarrolla el juego

    El juego se desarrolla en un único mapa compuesto por 3 zonas distintas conectadas entre sí, estas son:
    -	Aldea principal
    -	Bosque venenoso
    -	Pico nevado
	Nuestra idea inicial era añadir 2 zonas más: Cueva oscura y Castillo de Rowt, para un total de 5 zonas, pero no ha sido posible implementarlas a tiempo.
    	
	2.2.2	Número de niveles

	Como se ha definido en el apartado anterior nuestro juego no consta de niveles sino de un mapeado extenso con 3 zonas diferentes.

	2.2.3	Número de NPCs

    Enemigos menores:
    -	Enemigo que se mueve siguiendo un patrón horizontal.
    -	Enemigo que describe un movimiento horizontal en el aire entre dos puntos.
    -	Enemigo que describe un movimiento vertical en el aire entre dos puntos.
    -	Enemigo estático que dispara a la izquierda.
    -	Enemigo estático que dispara a la derecha.
    -	Enemigo que describe un movimiento horizontal aéreo entre 2 puntos y dispara hacia abajo al detectar al jugador.
    -	Enemigo aéreo que describe un movimiento cuadrado en sentido antihorario.
    -	Enemigo aéreo que describe un movimiento cuadrado en sentido horario.
    -	Enemigo que se mueve siguiendo un patrón horizontal pero que al entrar en su rango de visión, cambiará de dirección para perseguirte. Tanto el jefe como los orbitales hacen daño por contacto al jugador.
    
    Jefes:
    -	Jefe 1 (bosque): Enemigo aéreo que se teletransporta entre 5 puntos del mapa y tiene 4 orbitales girando alrededor suyo que cambian de patrón.
    -	Jefe 2 (montaña): Enemigo aéreo que sigue un patrón cuadrado en sentido antihorario y tiene 4 orbitales girando alrededor suya que cambian de posición. Tanto el jefe como los orbitales hacen daño por contacto al jugador.

	2.2.4	Número de armas

    -	Hacha como arma principal.
    -	Arco con flechas limitadas como arma secundaria
    -	Magia ofensiva que gasta un recurso de mana
 
3.	**Interfaz**

	3.1	Sistema visual
	
	3.1.1	HUD

    En la parte superior de la pantalla se encontrará la interfaz principal:
    -	En la parte superior izquierda ubicamos el indicador de la vida de nuestro personaje así como el indicador de magia o maná disponible del mismo justo debajo. Debajo del maná encontramos el número de monedas que tiene el jugador.
    -	En la parte central encontramos 2 iconos que indican tanto el arma secundaria como la magia equipadas. Si el arma secundaria es un arco, también se mostrarán las flechas disponibles.
    -	En la parte superior derecha se indican el tipo de pociones y el número que se posee de cada una de ellas. 

	3.1.2	Controles

	Teclado y Ratón:

    -	Saltar -> W
    -	Moverse hacia la izquierda -> A
    -	Moverse hacia la derecha -> D
    -	Agacharse -> S
    -	Dash (Desbloqueable) -> Espacio
    -	Salto escalada (Desbloqueable) ->W al alejarte de una pared y luego mantener pulsado hacia la pared. Puedes seguir haciendo salto escalada mientras haya pared.
    -	Usar poción de vida -> Q
    -	Usar poción de maná -> E
    -   Entrar a la tienda -> T
    -   Ver el inventario -> I
    -   Ver el mapa (necesitas comprarlo primero) -> M
    -   Interacción con los menús -> Flechas de dirección
    -	Arma principal -> click izquierdo del ratón
    -	Arma secundaria/magia -> click derecho del ratón
    -	Intercambiar entre arma secundaria y magia -> Pulsar rueda del ratón
    -	Menú de pausa/Salir de algunas pantallas -> Esc


	3.1.3	Menús

    -	Menú de inicio: Al empezar se mostrará en pantalla con el título del juego, los modos de juego explicados anteriormente y un acceso al apartado de controles.
    -	Menú de pausa: Nos permitirá salir al menú de inicio y acceder al apartado de opciones de sonido y los controles del juego.
    -	Herrería: Tipo de menú tienda accesible desde dentro del juego solo en los puntos localizados como este tipo de tienda. Permite al jugador comprar con dinero armamento y piezas de armadura equipables que otorgan stats.
    -	Tienda de comestibles: Tipo de menú tienda accesible desde dentro del juego solo en los puntos localizados como este tipo de tienda. Permite al jugador regenerar vida comprando estos items con dinero en el momento.
    -	Tienda de pociones: Tipo de menú tienda accesible desde dentro del juego solo en los puntos localizados como este tipo de tienda. Permite al usuario comprar pociones para regenerar vida y maná cuando éste decida utilizarlas.
    -	Tienda de mapa: Tipo de menú tienda accesible desde dentro del juego solo en los puntos localizados como este tipo de tienda. Permite al usuario comprar el mapa de la zona en la que se encuentra.
    -	Inventario: Este menú sirve para que el jugador pueda consultar los equipables que tiene y pueda intercambiarlos.
    -	Menú de muerte: Al morir el jugador aparece un menú desde el que el jugador podrá salir del juego o reanudar en juego desde el último checkpoint que tocó el jugador.


	3.1.4	Características del Motor 2D

    -	Mapeado separado en capas de dibujado. Sensación de profundidad.
    -	Carga de sprites y texturas.
    -	Mapeado del videojuego, dividido en zonas.
    -	Hitbox para enemigos, objetos, etc.
    -	Frames invulnerabilidad al recibir daño.

	3.1.5	Cámara

    La cámara estará centrada en el protagonista, haciendo scroll lateral y vertical por cada zona dentro del mapa siguiendo al personaje hasta topar con el borde del nivel.

	3.2	Sonido

	Música:
    -	Cada una de las zonas tendrá una música distinta que represente la estética y la ambientación de la misma.
    -	Cada uno de los jefes contará con una música distinta que refleje que no son enemigos corrientes.
    
	3.3	Sistema de ayuda

	Tanto en el menú principal como en el de pausa se muestran los controles del juego.
    
 4.	**Mecánicas**

	4.1	Reglas del juego explícitas e implícitas

	4.1.1	Física

    -	Gravedad: como juego dentro del género de las plataformas debemos implementar la gravedad para no echar a perder la jugabilidad.
    -	Colisiones: hay que tener en cuenta este apartado para la interacción entre el jugador, el mapa, los objetos y enemigos. Otras colisiones son las armas y hechizos del jugador con los enemigos.
    -	Velocidad/Movimiento: con la implementación del “dash” tendremos que jugar con la percepción del movimiento y velocidad que puede alcanzar el protagonista.

	4.1.2	Movimiento

    Para el movimiento usaremos los controles descritos en el apartado 3.1.2. El personaje podrá moverse y realizar un pequeño “dash” en horizontal. También contamos con el salto escalada, que te permite pegarse a la pared y saltar para avanzar en el eje vertical. Ambos movimientos adicionales se desbloquearán al derrotar a sus respectivos jefes de zona.

	4.1.3	Objetos

    -	Pociones: el jugador contará con dos tipos de pociones, una roja que hará que recupere vida y otra azul que recupere maná.
    -	Armas: el protagonista contará con un hacha como arma principal y con un arco como arma secundaria, que podrá ir cambiando con el equipamiento comprado en la tienda. Con el mismo botón también lanzará magia ofensiva de 2 tipos: fuego y hielo.
    -	Monedas: objeto que se consigue al derrotar enemigos y sirve para comprar diversas cosas durante el transcurso del juego como equipamiento o consumibles.
    -	Equipamiento: este se podrá adquirir mediante su compra en la aldea principal y mejorará las estadísticas base del jugador.
    -	Comestibles: estos hacen recuperar vida y maná al comprarlos.


    4.1.4	Acciones (interruptores, coger, dejar, hablar…)
	Las interacciones que se pueden realizar durante el juego son:
	- Comprar objetos
	- Consumir pociones y comida
	- Equipar objetos
	- Visualizar mapa
	- Ataque básico cuerpo a cuerpo
	- Agacharse
	- Saltar
	- "Salto escalada"
	- "Dash"


    4.1.5	Economía

    Al eliminar a los diferentes enemigos, se sumarán de forma aleatoria entre 1 a 5 monedas al matar el duende más básico y de 1 a 10 monedas el resto de enemigos. Esta moneda puede ser utilizada para comprar diferentes artículos en las distintas tiendas repartidas por todas las zonas del juego. Dichos objetos pueden ser equipamiento, pociones o el mapa de la zona en la que te encuentras.
    
    4.2	Transición de pantallas
    Primero en la pantalla se visualiza el logo de nuestra empresa Bugisoft seguido del menú inicial que te da opciones de jugar, ir a créditos o mostrar los controles. Al comenzar la aventura apareces en el juego desde el cual podrás ir a inventario o tiendas a placer. También se puede pausar el juego desde el cual se pueden ver los controles, volver al juego o volver al menú inicial. Por último, al morir puedes volver al juego desde el último checkpoint o ir al menú inicial.

    4.2.1	Diagrama de transición de pantallas
 		Se puede encontrar la imagen en el apartado "otros" de Github.
		
    4.2.2	Descripción de las pantallas
		- Pantalla principal: muestra el logotipo del equipo (Bugisoft).
		- Menú principal: muestra distintos apartados, consultar punto 4.2.4.
		- Controles: muestra una imagen con los controles del jugador.
		- Créditos: muestra los nombres de los integrantes del equipo.
		- Pantalla del juego: donde se desarrolla el transcurso del videojuego.
		- Menú pausa:  muestra distintos apartados, consultar punto 4.2.4.
		- Menú fin de juego: muestra distintos apartados, consultar punto 4.2.4.
		- Pantalla de tienda: muestra los distintos ítems que se pueden comprar dependiendo de qué tienda sea.
		- Inventario: muestra los ítems equipados así como todos los adquiridos, el número de pociones y dinero.

    6.2.3	Pantallas del juego
    7.2.4	Menús

-	Menú principal:
	-	Jugar
	-	Modo Boss Rush
	-	Opciones
	-	Controles
	-	Créditos
	-	Salir
-	Menú de pausa:
	-	Reanudar
	-	Opciones
	-	Salir al menú principal

- 	Menú fin de juego
	- 	Continuar desde el último checkpoint
	- 	Salir al menú principal

	4.3	Opciones del juego: cuáles son y cómo afectan a la mecánica

	El juego no dispondrá de opciones que afecten a la mecánica principal, sin embargo, contará con un submenú de opciones que nos permitirá realizar las siguientes acciones:
	-	Desactivar la música.
	-	Ver los controles del juego.
	-	Ver los créditos del juego.
	
	4.4	Rejugar y salvar
	- Modo historia: El mapa dispondrá de distintos checkpoints o puntos de guardado donde el jugador en caso de morir podrá elegir reaparecer en el último punto de guardado que ha tocado.
	- Modo Boss Rush (en desarrollo): Este modo no cuenta con puntos de guardado, sin embargo, contará con una opción en el menú de pausa que permitirá reiniciarlo.
    
	4.5	Trucos y Easter Eggs

	- Trucos:	
		- Pulsar la tecla F1 activa las habilidades desbloqueables tras derrotar los bosses.
		- Pulsar la tecla F10 te otorgará 1000 monedas.
		- Pulsar la tecla F11 activará el modo Invencible, que consiste en que el jugador se volverá inmortal y dispondrá de saltos infinitos.
		- Pulsar la tecla F12 modo debug, donde se muestran las hitbox del jugador y de los enemigos.


5.	**Historia, características y personajes**

	5.1	Historia

    En un pequeño pueblo llamado Etria, perteneciente al reino de Rhodianur, Uthric, un mago malvado de otro reino ha provocado un diluvio que ha anegado tanto casas como campos y ha arruinado los cultivos de Dunstan Leofstan, nuestro protagonista.

    Dunstan, que es un granjero con alma de héroe, se embarcará en una aventura en la que tendrá que explorar las tierras del reino para derrotar a Uthric y sus secuaces con el fin de salvar a su aldea del diluvio y recuperar su campo.

	5.2	Mundo del juego

	-	Zona 1 – Aldea Principal:
    Es la zona donde empieza la historia del personaje. La aldea de Etria forma parte del reino de Rhodianur, ahora anegada por la lluvia. En ella encontraremos un par de tiendas que permitirán adquirir equipamiento y pociones.

	-	Zona 2 – Bosque Venenoso:
    El bosque es la zona más cercana a la aldea, éste ha sido corrompido por la magia de uno de los secuaces de Uthric que allí habita y lo ha convertido en un bosque venenoso lo que disminuirá la vida del protagonista de forma gradual.

	-	Zona 3 – Pico Nevado:
La montaña de Rhodianur, antaño llena de vida, ha sido cubierta de nieve debido a una tormenta que nunca termina y ahora se la conoce como Pico Nevado. SI desciendes por la montaña llegarás a las cavernas, un hervidero de enemigos En esta montaña el protagonista encontrará numerosas zonas de pinchos, y si desciende encontrará zonas de lava con numerosos enemigos.

	5.3	Personajes

    Personaje 1 – Dunstan Leofstan

    Dunstan Leofstan es el protagonista de este videojuego y un granjero más de la aldea de Etria, le gusta tener una vida tranquila cuidando de sus cultivos pero posee un fuerte sentido de la justicia, por eso, cuando el mago Uthric desata un diluvio sobre sus tierras destrozando la aldea y echando a perder sus cultivos se arma de valor y se embarca en una aventura con el fin de derrotarlo y hacer que la lluvia cese.
    Dunstan es un hombre risueño y humilde, aunque muy valiente que no puede ver sufrir a su gente. Es un hombre adulto, alto y fuerte debido a las numerosas jornadas de trabajo en el campo.

    Personaje 2 – Uthric

    Uthric, el antagonista de esta historia, se desconoce su apellido pues pocos son los que han sobrevivido a su encuentro. Uthric es humano, aunque oculta su apariencia tras su vestimenta, domina la magia y las artes arcanas con gran precisión, pero durante sus estudios sucumbió a la magia oscura y ahora su único objetivo es sembrar el caos.
    Se dice que Uthric es frío como un témpano de hielo y que parece carecer de emociones. Se desconocen sus rasgos humanos.
 
6.	**Niveles**
	No hay niveles en nuestro juego. El juego consta de diferentes zonas por las que el jugador podrá enfrentarse a diferentes enemigos y bosses.
 
7.	**Inteligencia Artificial**

	7.1	IA del oponente

	Tenemos diferentes enemigos menores y cada tipo de enemigo tendrá una IA distinta:

	-	Enemigo 1: 
este enemigo se moverá de manera permanente entre 2 puntos del eje horizontal por el SUELO. Causará daño al jugador si colisiona con él.

    -	Enemigo 2: 
este enemigo se moverá de manera permanente entre 2 puntos del eje horizontal por el AIRE. Causará daño al jugador si colisiona con él.

    -	Enemigo 3: 
este enemigo se moverá de manera permanente entre 2 puntos del eje vertical por el AIRE. Causará daño al jugador si colisiona con él.

	-	Enemigo 4:
este enemigo permanecerá estático y lanzará proyectiles hacia la DERECHA al jugador cuando éste entre en su radio de acción. Los proyectiles que impacten con el jugador causarán daño, además causará daño si el jugador colisiona con él.

	-	Enemigo 5:
este enemigo permanecerá estático y lanzará proyectiles hacia la IZQUIERDA al jugador cuando éste entre en su radio de acción. Los proyectiles que impacten con el jugador causarán daño, además causará daño si el jugador colisiona con él.

	-	Enemigo 6: 
este enemigo se moverá inicialmente igual que el Enemigo 4 pero no cambiará su patrón al entrar en su radio de acción, sin embargo, lanzará proyectiles hacia ABAJO al jugador. Este enemigo causa daño mediante colisión con él y si los proyectiles impactan al jugador. 

    -	Enemigo 7: 
enemigo que se MUEVE realizando un CUADRADO entre 4 PUNTOS en el AIRE. Orden del movimiento -> DERECHA - ARRIBA - IZQUIERDA - ABAJO.

    -	Enemigo 8: 
enemigo que se MUEVE realizando un CUADRADO entre 4 PUNTOS en el AIRE. Orden del movimiento -> IZQUIERDA - ARRIBA - DERECHA - ABAJO.

	-	Enemigo 9:
este enemigo se moverá principalmente como el Enemigo 1 hasta que el jugador entre en su radio de acción y empezará a perseguirlo. Este enemigo solo causa daño por colisión con el jugador.

A parte de los enemigos menores habrá 2 jefes de zona
	- Jefe 1: Enemigo aéreo que se teletransporta entre 5 puntos del mapa y tiene 4 orbitales girando alrededor suyo que cambian de patrón.
	- Jefe 2: Enemigo aéreo que sigue un patrón cuadrado en sentido antihorario y tiene 4 orbitales girando alrededor suya que cambian de posición. Tanto el jefe como los orbitales hacen daño por contacto al jugador.



8.	**Diseño de software**

	8.1	Diagramas
		Consultar en imágenes en el apartado “otros” de Github.

	8.2	Patrones de diseño
		- Singleton: Hemos implementado 3 patrones singleton en nuestro juego, Motor2D, el estado de juego y el jugador.
		- Fachada: Se ha creado Motor2D como clase fachada.

 
9.	**Motores**

	9.1	Motor 2D
		Como se ha mencionado en el punto anterior, el Motor 2D se ha implementado en la clase Motor2D como fachada. 

	9.2	Física
		Tanto el jugador como los enemigosgestionan sus propias fisicas y colisiones. Estas últimas están realizadas con bounding boxes.
		Se toman 4 puntos tanto del jugador como de los enemigos, estos puntos forman una caja alrededor de ellos. Comparando las posiciones de estos puntos podemos averiguar si 2 o más cajas están en contacto directo si se da el caso de que uno de los puntos de una caja está dentro de otra. Esto también se aplica a las colisiones con los proyectiles del juego.
Para las colisiones del jugador, los enemigos y los proyectiles con el mapa se aplica el mismo principio de los 4 puntos pero esta vez se comparan con la posición que ocupan dentro de una matriz que alberga todos los tiles del mapa; así podemos conocer con qué tiles exactamente están colisionando.
En cuanto a la física básica de movimiento todo se mueve mediante el uso de velocidades y se les limita el movimiento mediante las colisiones.

 
10.	**Dirección y planificación**

	10.1	Ejecutables a entregar
	
	-	Hito 1
    
		-	jecutable con movimiento básico y salto.
		-	Ejecutable con menú de pausa.
		-	Ejecutable con mapa de prueba cargado y dibujado.
		-	Ejecutable con IA de enemigo básica.
		-	Ejecutable con interfaz básica.
	
	-	Hito 2
		-	Ejecutable con la versión beta del juego.
	
	-	Hito 3
		-	Ejecutable con la versión final del juego.

	10.2 Funcionalidades básicas por entregable

	- Hito 1

		1.	Moverse y saltar (Alba): el personaje podrá moverse en horizontal en ambos sentidos, hacia arriba saltando y hacia abajo cayendo, también se puede agachar.
		2.	Menú de pausa (Ángel): el menú de pausa contendrá los submenús explicados en el punto 4.2.4.
		3.	Hitbox de los personajes: detección de colisiones que se indicará mediante cambio de color con los objetos creados.
		4.	Cargar sprites básicos: cargar Sprite del personaje, sin animaciones.
		5.	Mapas (Alfredo): diseñar un mapa básico, cargarlo y dibujarlo.
		6.	Inteligencia artificial básica (Antonio David): IA de enemigos básica. Patrón de movimiento del Enemigo 1 explicado en el punto 7.1.
		7.	Sprites y animación: cargar el Sprite del personaje y hacer que cambie al moverse y saltar.

	- Hito 2 

      1.	Menú principal básico: se realizará el menú que se cargará al iniciar el juego con los apartados explicados en el punto 4.2.4.
      2.	Personaje principal: cargar una hoja de sprites del personaje principal y controlarlo.
      3.	Mecánica de ataque: al pulsar la tecla designada para ello aparecerá una pequeña hitbox delante del personaje que detectará si ha colisionado con otro objeto. Esta colisión también se mostrará mediante el cambio de color.
      4.	Cámara: se implementará una cámara que siga al jugador realizando scroll del mapa.
      5.	IA adicional: se implementará otra IA de enemigo de las explicadas en el punto 7.1.
      6.	Detección de colisiones: Mapa cargado detectando colisiones con jugador y enemigos con el entorno.
      7.	Implementación de power-up 1: Implementar el primer power-up, el dash.
      8.	Implementación de power-up 2: Implementar el segundo power-up de movimiento, el doble salto.
      9.	Implementación de power-up 3: Implementar el tercer power-up, el salto escalada.
      10.	Implementar mapa completo: Mapa terminado y conectado en su totalidad.
      11.	Implementar transición entre pantallas: Pequeña animación de cambio de zona para cargar la parte del mapa.

	- Hito 3
      1.	Revisar bugs y errores.
      2.	Añadir funcionalidades opcionales.
      3.	Cuestiones menores como detalles de visibilidad y feedback para el jugador.
      4.	Juego terminado.

	10.3 Funcionalidades opcionales

	-	Modo oleadas.
	-	Modo Boss Rush
	-	Armas secundarias opcionales.

