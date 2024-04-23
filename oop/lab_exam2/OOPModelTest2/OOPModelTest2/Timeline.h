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
	//shared_ptr<Superhero> attacker;
	//shared_ptr<Superhero> defender;
	float life, shield, damage, energy;
	TimelineEvent(Superhero& att, Superhero& def)
	{
		attacker = &att;
		defender = &def;
		life = defender->get_life();
		shield = defender->get_shield();
		damage = attacker->get_dmg();
		energy = attacker->get_energy();
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

