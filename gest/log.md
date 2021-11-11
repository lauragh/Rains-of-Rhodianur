# Log del trabajo realizado por dia
**El log es obligatorio**

## 20210108 FidelAznar @(1h)
Debe contener un sub item como el anterior, con la fecha de la entrada y las cuestiones generales que se realizaron, así como el tiempo total dedicado en la sesión. 

## 20210308 Alfredo Pérez (~3h)
Querido diario, he comenzado con la clase mapa, pero al final me he puesto a ver los videos de fidel sobre la lectura d ficheros tmx y la carga del mapa. He trabajado un poco haciendo el .h y el .cpp.

## 20210310 Alfredo Pérez (~4h)
Querido diario, hoy he hecho la lectura del fichero XML para obtener los datos del mapa que hacemos en Tiled. Posibles sitios donde puede fallar, una vez arregle los errores de compilación: 

**Mapa.cpp**
- Lineas 78-81->QueryInitAttribute de un tile que no tiene GID: no sé si devuelve un mensaje "XML_NO_ATTRIBUTE" o directamente el código 2. Cuando pueda ejecutar el código lo comprobaré.


## 20210310 Alba Ruiz (6h)
Hoy he arreglado bastante prácticamente todo lo que tenía hecho de código, ya que tenía ya empezada la clase personaje como tal pero seguía sin moverse correctamente. Se me ha corrompido el repositorio en local por lo que he tenido que volver a clonarlo, pero todo lo que había hecho lo tenía en una copia local aparte. Ahora el jugador puede moverse hacia los lados, saltar y caerse de una plataforma.

## 20210311 Alfredo Pérez (~3h)
Querido diario, he terminado la lectura del fichero xml y comprobado que funciona correctamente. El dibujado del mapa apenas lo he empezado, pero porque he estado buscando información sobre como hacerlo.

## 20210312 Alfredo Pérez (~4h)
Querido diario, completado el dibujado del mapa y que se dibuje por capas (gracias Alba). No está implementada la matriz de colisiones aún, quiero probar a usar el vertexArray de la capa principal, que ya está creado y se usa en el dibujado, en lugar de crear otra matriz idéntica.

## 20210310 Laura García (~3h y media)
He arreglado el problema del string y he pensado cómo hacer que el personaje refleje cuales son sus puntos actuales de vida y mana, tanto en número como en barra. He añadido el uso de pociones de vida y mana

## 20210310 Laura García (~3h y media)
He reestructurado mi código para dejarlo más claro y limpio y he hecho que la interfaz siga al "personaje" cuando este se mueva.

## 20210322 Laura García (30 min)
He añadido mi clase interfaz pero necesito un jugador para poder implementarlo correctamente y saber cómo funciona el motor2d.
He empezado a mirar para crear un mapa.
## 20210330 Alfredo Pérez Pinedo (~5h y media)
Querido diario, he puesto el prototipo de mapas en el proyecto conjunto y he añadido la matriz con la que haremos las colisiones con el mapa. También he hecho que podamos guardarnos la posición de los enemigos cuando cargamos el mapa, para poder colocarlos desde el tiled. 

## Entrega de log

## 20210330 Antonio David Ortiz (~3h y cuarto)
He empezado con la estructura de los niveles y he retocado los enemigos, necesito unos datos del mapa para continuar.