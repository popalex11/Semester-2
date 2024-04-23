#pragma once
#include "Superhero.h"
class Human :
    public Superhero
{
public:
    void attack(Superhero&) override;
    Human(int, const string&, float, float, float, float);
};

