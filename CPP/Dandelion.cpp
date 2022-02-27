#include "Dandelion.h"

#define DANDELION_POWER 0
#define DANDELION_INITIATIVE 0
#define DANDELION_SOW 3

Dandelion::Dandelion(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'D';
	this->initiative = DANDELION_INITIATIVE;
	this->power = DANDELION_POWER;
	this->name = "Dandelion";
}

Organism* Dandelion::make_baby(int born_day, int position)
{
	Organism* new_organism = new Dandelion(world, born_day, position);
	return new_organism;
}

void Dandelion::action()
{
	for (int i = 0; i < DANDELION_SOW; i++)
		Plant::action();
}