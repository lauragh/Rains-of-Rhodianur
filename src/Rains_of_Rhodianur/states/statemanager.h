#pragma once

#include <memory>
#include <stack>

#include "state.h"

/*CLASE QUE CONTROLA EL FLUJO DE ESTADOS DEL JUEGO
ALMACENADOS EN UNA PILA DE ESTADOS*/

typedef  std::unique_ptr<State> state_ptr; // shortcut

class StateManager
{
    private :
        std::stack<state_ptr>   states;
        state_ptr               newState;
        
        bool add;
        bool remove;
        bool replace;

    public:
        StateManager(){};
        ~StateManager(){};

        /*Método para añadir un estado nuevo*/
        void addState(state_ptr stateAdded, bool replace = true);
        /*Método para cambiar de estado*/
        void popState();
        /*Procesa los cambios hechos a los estados*/
        void changeState();
        /*Devuelve el estado actual*/
        state_ptr& getCurrentState();
};