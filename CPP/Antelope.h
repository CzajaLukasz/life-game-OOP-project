#pragma once
#include "Animal.h"

class Antelope : public Animal
{
public:
	Antelope(World* world, int born_day, int position);
	Antelope(World* world, int born_day, int position, int power);
	int draw_place();
	void action() override;
	int collision(Organism* attacker) override;
	Organism* make_baby(int born_day, int position) override;
};