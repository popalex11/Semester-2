#include "Timeline.h"

void Timeline::RollBackTime(int k)
{
	while (k > 0 && !timeline.empty())
	{
		k--;
		TimelineEvent e = timeline.top();
		e.attacker->set_energy(e.energy);
		e.defender->set_life(e.life);
		e.defender->set_shield(e.shield);
		e.defender = nullptr;
		delete e.defender;
		e.attacker = nullptr;
		delete e.attacker;
		timeline.pop();
	}
}

void Timeline::Event(Superhero& attacker, Superhero& defender)
{
	TimelineEvent ev{attacker, defender};
	timeline.push(ev);
}

Timeline::~Timeline()
{
	while (!timeline.empty())
	{
		timeline.top().attacker = nullptr;
		timeline.top().defender = nullptr;
		delete timeline.top().attacker;
		delete timeline.top().defender;
		timeline.pop();
	}
}
