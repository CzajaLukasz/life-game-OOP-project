#include "Sheep.h"

#define SHEEP_POWER 4
#define SHEEP_INITIATIVE 4

Sheep::Sheep(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'S';
	this->initiative = SHEEP_INITIATIVE;
	this->power = SHEEP_POWER;
	this->name = "Sheep";
}

Sheep::Sheep(World* world, int born_day, int position, int power)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'S';
	this->initiative = SHEEP_INITIATIVE;
	this->power = power;
	this->name = "Sheep";
}

Organism* Sheep::make_baby(int born_day, int position)
{
	Organism* new_organism = new Sheep(world, born_day, position);
	return new_organism;
}