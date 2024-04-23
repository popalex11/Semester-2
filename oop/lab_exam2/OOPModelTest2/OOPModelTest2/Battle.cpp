#include "Battle.h"

void Battle::add_hero(unique_ptr<Superhero>& hero)
{
	heroes.push_back(std::move(hero));
}