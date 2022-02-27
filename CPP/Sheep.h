#pragma once
#include "Animal.h"

class Sheep : public Animal
{
public:
	Sheep(World* world, int born_day, int position);
	Sheep(World* world, int born_day, int position, int power);
	Organism* make_baby(int born_day, int position) override;
};