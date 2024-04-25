#pragma once
#include "Superhero.h"
#include "Timeline.h"
class Timeline;
class Deity : public Superhero
{
public:
	void attack(Superhero&) override;
	Deity(int, const string&, float, float, float, float);
	void RollBackTime(Timeline& ,int);
};

