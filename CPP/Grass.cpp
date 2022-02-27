#include "Grass.h"

#define GRASS_POWER 0
#define GRASS_INITIATIVE 0

Grass::Grass(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = '.';
	this->initiative = GRASS_INITIATIVE;
	this->power = GRASS_POWER;
	this->name = "Grass";
}

Organism* Grass::make_baby(int born_day, int position)
{
	Organism* new_organism = new Grass(world, born_day, position);
	return new_organism;
}