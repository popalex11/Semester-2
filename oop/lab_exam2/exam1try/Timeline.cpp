#include "Timeline.h"


void Timeline::RollBackTime(int time)
{
    while (time>0 && !timeline.empty())
    {
        time--;
        TimelineEvent e = timeline.top();
        e.attacker->setEnergy(e.energy);
        e.defender->setShield(e.shield);
        e.defender->setLife(e.life);
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
    while(!timeline.empty()){
        timeline.top().attacker = nullptr;
        delete timeline.top().attacker;
        timeline.top().defender = nullptr;
        delete timeline.top().defender;
        timeline.pop();
    }
}