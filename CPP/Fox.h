#pragma once
#include "Animal.h"

class Fox : public Animal
{
public:
	Fox(World* world, int born_day, int position);
	Fox(World* world, int born_day, int position, int power);
	int draw_place();
	void action() override;
	Organism* make_baby(int born_day, int position) override;
};