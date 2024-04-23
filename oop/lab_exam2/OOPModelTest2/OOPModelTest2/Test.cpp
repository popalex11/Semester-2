#include "Test.h"

void TestBattle()
{
	Battle battle;
	Timeline timeline;
	unique_ptr<Superhero> dave( new Human(1,"Dave",1,1,1,10) );
	unique_ptr<Superhero> johnsuperhero(new Deity(2, "John", 10, 10, 10, 10));
	battle.add_hero(dave);
	battle.add_hero(johnsuperhero);
	
	timeline.Event(*battle.heroes[0], *battle.heroes[1]);
	battle.heroes[0]->attack(*battle.heroes[1]);
	assert(battle.heroes[0]->get_energy() == 9);
	assert(battle.heroes[1]->get_shield() == 9);
	assert(battle.heroes[1]->get_life() == 10);

	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline,1);
	assert(battle.heroes[0]->get_energy() == 10);
	assert(battle.heroes[1]->get_shield() == 10);
	assert(battle.heroes[1]->get_life() == 10);

	timeline.Event(*battle.heroes[0], *battle.heroes[1]);
	battle.heroes[0]->attack(*battle.heroes[1]);
	assert(battle.heroes[0]->get_energy() == 9);
	assert(battle.heroes[1]->get_shield() == 9);
	assert(battle.heroes[1]->get_life() == 10);

	timeline.Event(*battle.heroes[0], *battle.heroes[1]);
	battle.heroes[0]->attack(*battle.heroes[1]);
	assert(battle.heroes[0]->get_energy() == 8);
	assert(battle.heroes[1]->get_shield() == 8);
	assert(battle.heroes[1]->get_life() == 10);

	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline, 2);
	assert(battle.heroes[0]->get_energy() == 10);
	assert(battle.heroes[1]->get_shield() == 10);
	assert(battle.heroes[1]->get_life() == 10);

	timeline.Event(*battle.heroes[1], *battle.heroes[0]);
	battle.heroes[1]->attack(*battle.heroes[0]);
	assert(battle.heroes[1]->get_energy() == 9);
	assert(battle.heroes[0]->get_shield() == 0);
	assert(battle.heroes[0]->get_life() <=0);
	
	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline, 2);
	assert(battle.heroes[1]->get_energy() == 10);
	assert(battle.heroes[0]->get_shield() == 1);
	assert(battle.heroes[0]->get_life() == 1);
}
