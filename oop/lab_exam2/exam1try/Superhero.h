#pragma once 
#include <string>
using std::string;

class Superhero
{
protected:
    int ID;
    string name;
    float life, damage, shield, energy;

public:
    Superhero(int, const string&, float, float, float, float);
    Superhero(const Superhero&);
    const int getID() const;
    const string& getName() const;
    const float getLife() const;
    const float getDamage() const;
    const float getShield() const;
    const float getEnergy() const;
    void setLife(const float);
    void setDamage(const float);
    void setShield(const float);
    void setEnergy(const float);
    virtual void attack(Superhero&) = 0;
};