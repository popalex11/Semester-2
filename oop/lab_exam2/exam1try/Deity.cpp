#include "Deity.h"

Deity::Deity(int id, const string& name, float life, float damage, float shield, float energy):
    Superhero(id, name, life, damage, shield, energy)
{
    
}

void Deity::attack(Superhero& other)
{
    if (this-> energy > 0)
    {
        this->energy--;
        other.setShield(other.getShield() - this->damage);
        if (other.getShield() <0)
        {
            other.setLife(other.getLife() + other.getShield());
            other.setShield(0);
        }
    }
}

void Deity::RollBackTime(Timeline& timeline, int time)
{
    timeline.RollBackTime(time);
}


