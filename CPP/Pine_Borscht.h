#pragma once
#include "Plant.h"

class Pine_Borscht : public Plant
{
public:
	Pine_Borscht(World* world, int born_day, int position);
	int collision(Organism* attacker) override;
	void action() override;
	Organism* make_baby(int born_day, int position) override;
};