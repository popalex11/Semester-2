#include "Human.h"

void Human::attack(Superhero& other)
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

Human::Human(int id, const string& name, float life, float damage, float shield, float energy):
    Superhero(id, name, life, damage, shield, energy)
{
    
}