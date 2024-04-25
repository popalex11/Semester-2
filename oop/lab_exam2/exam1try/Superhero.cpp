#include "Superhero.h"

Superhero::Superhero(int id, const string& name, float life, float damage, float shield, float energy)
{
    ID = id;
    this->name = name;
    this->life = life;
    this->damage = damage;
    this->shield = shield;
    this->energy = energy;
}

Superhero::Superhero(const Superhero& other)
{
    this->ID = other.getID();
    this->name = other.getName();
    this->life = other.getLife();
    this->damage = other.getDamage();
    this->shield = other.getShield();
    this->energy = other.getEnergy();
}

const int Superhero::getID() const
{
    return ID;
}

const string& Superhero::getName() const
{
    return name;
}

const float Superhero::getLife() const
{
    return life;
}

const float Superhero::getDamage() const
{
    return damage;
}

const float Superhero::getShield() const
{
    return shield;
}

const float Superhero::getEnergy() const
{
    return energy;
}

void Superhero::setLife( float life2)
{
    life = life2;
}

void Superhero::setDamage( float damage)
{
    this->damage = damage;
}

void Superhero::setShield( float shield)
{
    this->shield = shield;
}

void Superhero::setEnergy( float energy)
{
    this->energy = energy;
}



