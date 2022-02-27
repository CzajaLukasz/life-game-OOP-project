#pragma once
#include "Plant.h"

class Guarana : public Plant
{
public:
	Guarana(World* world, int born_day, int position);
	Organism* make_baby(int born_day, int position) override;
	int collision(Organism* attacker) override;
};