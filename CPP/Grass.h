#pragma once
#include "Plant.h"

class Grass : public Plant
{
public:
	Grass(World* world, int born_day, int position);
	Organism* make_baby(int born_day, int position) override;
};