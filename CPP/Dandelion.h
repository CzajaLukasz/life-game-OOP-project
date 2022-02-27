#pragma once
#include "Plant.h"

class Dandelion : public Plant
{
public:
	Dandelion(World* world, int born_day, int position);
	Organism* make_baby(int born_day, int position) override;
	void action() override;
};