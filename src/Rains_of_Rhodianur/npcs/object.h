#pragma once

#include <SFML/Graphics.hpp>
#include "../npcs/object.h" 
#include <iostream>

struct Stats
{
    float armour;
    float mana;
    float damage;
    float health;
    int amount_consume;
};


class Object{
    private:
    
    std::string name;
    std::string type;
    Stats stats;
    int cost;
    bool bought;
    std::string description;
    int columna;
    int fila;
   
    public:
    Object(std::string name0, std::string type0, float damage0,float armour0, float mana0, int amount_consume0,float health0, int cost0, bool bought0, std::string description0,int columna, int fila);
    ~Object();
    Object(const Object&);
    Object& operator = (const Object &o);
    
    std::string getName();
    std::string getType();
    Stats getStats();
    std::string getDescription();
    int getCost();
    int getColumna();
    int getFila();
    bool isBought();
    
    void buy();
};