#include "Deity.h"

Deity::Deity(int id, const string& n, float l, float d, float sh, float en):
	Superhero(id,n,l,d,sh,en)
{

}

void Deity::attack(Superhero& other)
{
	if (this->energy > 0)
	{
		this->energy--;
		other.set_shield(other.get_shield() - this->dmg);
		if (other.get_shield() < 0)
		{
			other.set_life(other.get_life() + other.get_shield());
			other.set_shield(0);
		}
	}
}

void Deity::RollBackTime(Timeline& timeline, int k)
{
	timeline.RollBackTime(k);
}