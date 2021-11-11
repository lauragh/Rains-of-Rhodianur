#include "../npcs/object.h"

Object::Object(std::string name0, std::string type0, float damage0,float armour0, float mana0, int amount_consume0,float health0, int cost0, bool bought0, std::string description0, int columna0, int fila0){
    
    name = name0;
    type = type0;
    stats.mana = mana0;
    stats.armour = armour0;
    stats.damage = damage0;
    stats.health = health0;
    stats.amount_consume = amount_consume0;
    cost = cost0;
    bought = bought0;
    description = description0;
    columna = columna0;
    fila = fila0;
}

Object::~Object(){
    name ="";
    type ="";
    stats.mana = 0;
    stats.armour =0;
    stats.damage =0;
    stats.health =0;
    stats.amount_consume = 0;
    cost = 0;
    bought = false;
    description ="";
    columna = 0;
    fila = 0;
}

Object::Object(const Object& o){
    name = o.name;
    type = o.type;
    stats.mana = o.stats.mana;
    stats.armour = o.stats.armour;
    stats.damage = o.stats.damage;
    stats.health = o.stats.health;
    stats.amount_consume = o.stats.amount_consume;
    cost = o.cost;
    bought = o.bought;
    description = o.description;
    columna = o.columna;
    fila = o.fila; 
}

Object& Object::operator = (const Object &o)
{
    if(this!=&o){ //Comprueba que no se esté intentanod igualar un objeto a sí mismo
        name = o.name;
        type = o.type;
        stats.mana = o.stats.mana;
        stats.armour = o.stats.armour;
        stats.damage = o.stats.damage;
        stats.health = o.stats.health;
        stats.amount_consume = o.stats.amount_consume;
        cost = o.cost;
        bought = o.bought;
        description = o.description;
        columna = o.columna;
        fila = o.fila;
    }
    return *this;
}
    
std::string Object::getName(){
    return name;
}

std::string Object::getType(){
    return type;
}

Stats Object::getStats(){
    return stats;
}

std::string Object::getDescription(){
    return description;
}
    
int Object::getCost(){
    return cost;
}

bool Object::isBought(){
    return bought;
}
    
void Object::buy(){
    bought = true;
}

int Object::getColumna(){
    return columna;
}

int Object::getFila(){
    return fila;
}