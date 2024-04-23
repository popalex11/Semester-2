#pragma once
#include <string>
using std::string;
class Superhero
{
protected:
	int ID;
	string name;
	float life, dmg, shield, energy;
public:
	Superhero(int, const string&, float, float, float, float);
	Superhero(const Superhero&);
	const int get_ID() const;
	const string& get_name()const;
	const float get_life() const;
	void set_life(float);
	const float get_dmg() const;
	void set_dmg(float);
	const float get_shield() const;
	void set_shield(float);
	const float get_energy() const;
	void set_energy(float);
	virtual void attack(Superhero&) = 0;
};

