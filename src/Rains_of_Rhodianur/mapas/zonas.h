
#pragma once

#include <iostream>
#include <map>
#include "../motor2D/enemy.h"
#include "../mapas/Mapa.h"


class zonas {

    private:

        const char* pathmap;

    public:
        int totalenemylvl;
        std::map<int, Enemy*> enemylist;

        Mapa *mapactual;
        int idMapa;
        void crearZona(int);

        zonas();
        ~zonas();
};

