#pragma once
#include "Plant.h"

class Berries : public Plant
{
public:
	Berries(World* world, int born_day, int position);
	Organism* make_baby(int born_day, int position) override;
	int collision(Organism* attacker) override;
};