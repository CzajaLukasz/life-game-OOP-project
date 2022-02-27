#pragma once
#include "Animal.h"

class Turtle : public Animal
{
public:
	Turtle(World* world, int born_day, int position);
	Turtle(World* world, int born_day, int position, int power);
	void action() override;
	int collision(Organism* attacker) override;
	Organism* make_baby(int born_day, int position) override;
};