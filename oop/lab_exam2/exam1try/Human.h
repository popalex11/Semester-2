#pragma once
#include "Superhero.h"

class Human:
    public Superhero
{
public:
    Human(int, const string&, float, float, float, float);
    void attack(Superhero&) override;
};