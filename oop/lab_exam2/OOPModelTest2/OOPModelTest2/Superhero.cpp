#include "Superhero.h"

Superhero::Superhero(int id, const string& name, float life, float dmg, float shield, float energy)
{
	ID = id;
	this->name = name;
	this->life = life;
	this->dmg = dmg;
	this->shield = shield;
	this->energy = energy;
}

Superhero::Superhero(const Superhero& hero)
{
	this->ID = hero.get_ID();
	this->name = hero.get_name();
	this->shield = hero.get_shield();
	this->life = hero.get_life();
	this->dmg = hero.get_dmg();
	this->energy = hero.get_energy();
}

const int Superhero::get_ID() const
{
	return ID;
}

const string& Superhero::get_name() const
{
	return name;
}

const float Superhero::get_life() const
{
	return life;
}

void Superhero::set_life(float l)
{
	life = l;
}

const float Superhero::get_dmg() const
{
	return dmg;
}

void Superhero::set_dmg(float d)
{
	dmg = d;
}

const float Superhero::get_shield() const
{
	return shield;
}

void Superhero::set_shield(float sh)
{
	shield = sh;
}

const float Superhero::get_energy() const
{
	return energy;
}

void Superhero::set_energy(float en)
{
	energy = en;
}
