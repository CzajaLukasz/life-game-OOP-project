#pragma once
#include "Animal.h"

class Wolf : public Animal
{
public:
	Wolf(World* world, int born_day, int position);
	Wolf(World* world, int born_day, int position, int power);
	Organism* make_baby(int born_day, int position) override;
};