#pragma once
#include "Superhero.h"
#include <memory>
using std::unique_ptr;
#include <vector>
using std::vector;

class Battle
{
public:
	vector<unique_ptr<Superhero>> heroes;
public:
	void add_hero(unique_ptr<Superhero>&);
};

