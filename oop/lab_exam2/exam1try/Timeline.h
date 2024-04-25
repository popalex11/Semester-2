#pragma once
#include "Superhero.h"
#include <stack>
#include <memory>
using std::stack;
using std::shared_ptr;
struct TimelineEvent
{
	Superhero* attacker;
	Superhero* defender;
	float life, shield, damage, energy;
	TimelineEvent(Superhero& att, Superhero& def)
	{
		attacker = &att;
		defender = &def;
		life = defender->getLife();
		shield = defender->getShield();
		damage = attacker->getDamage();
		energy = attacker->getEnergy();
	}
};
class Timeline
{
private:
	stack<TimelineEvent> timeline;

public:
	void RollBackTime(int);

	void Event(Superhero&, Superhero&);

	~Timeline();
};

