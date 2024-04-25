#include "test.h"
#include <iostream>

using std::cout;
using std::endl;
using std::unique_ptr;


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
	assert(battle.heroes[0]->getEnergy() == 9);
	assert(battle.heroes[1]->getShield() == 9);
	assert(battle.heroes[1]->getLife() == 10);

	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline,1);
	assert(battle.heroes[0]->getEnergy() == 10);
	assert(battle.heroes[1]->getShield() == 10);
	assert(battle.heroes[1]->getLife() == 10);

	timeline.Event(*battle.heroes[0], *battle.heroes[1]);
	battle.heroes[0]->attack(*battle.heroes[1]);
	assert(battle.heroes[0]->getEnergy() == 9);
	assert(battle.heroes[1]->getShield() == 9);
	assert(battle.heroes[1]->getLife() == 10);

	timeline.Event(*battle.heroes[0], *battle.heroes[1]);
	battle.heroes[0]->attack(*battle.heroes[1]);
	assert(battle.heroes[0]->getEnergy() == 8);
	assert(battle.heroes[1]->getShield() == 8);
	assert(battle.heroes[1]->getLife() == 10);

	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline, 2);
	assert(battle.heroes[0]->getEnergy() == 10);
	assert(battle.heroes[1]->getShield() == 10);
	assert(battle.heroes[1]->getLife() == 10);

	timeline.Event(*battle.heroes[1], *battle.heroes[0]);
	battle.heroes[1]->attack(*battle.heroes[0]);
	assert(battle.heroes[1]->getEnergy() == 9);
	assert(battle.heroes[0]->getShield() == 0);
	assert(battle.heroes[0]->getLife() <=0);
	
	static_cast<Deity*>(battle.heroes[0].get())->RollBackTime(timeline, 2);
	assert(battle.heroes[1]->getEnergy() == 10);
	assert(battle.heroes[0]->getShield() == 1);
	assert(battle.heroes[0]->getLife() == 1);

    cout<<"test passed"<<endl;
}
