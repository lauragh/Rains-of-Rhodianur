#pragma once

/*CLASE BASE PARA TODOS LOS ESTADOS DEL JUEGO*/

class State
{
    public:
        State(){};
        virtual ~State(){};
        /*EL SETUP INICIAL DEL ESTADO OCURRE EN ESTE METODO*/
        virtual void Init() = 0;
        /*METODO ENCARGADO DE PROCESAR LOS EVENTOS DEL ESTADO*/
        virtual void HandleInput() = 0;
        /*SE ENCARGA DE ACTUALIZAR TODOS LOS CAMBIOS DEL ESTADO.
        SE LE PASA POR PARAMETRO EL TIEMPO TRANSCURRIDO DESDE 
        LA ULTIMA LLAMADA A UPDATE()*/
        virtual void Update(const float& delta) = 0;
        /*DIBUJA TODOS LOS ELEMENTOS EN LA PANTALLA*/
        virtual void Render(const float& delta) = 0;

        virtual void Pause(){}
        virtual void Resume(){}

};