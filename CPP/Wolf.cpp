#include "Wolf.h"

#define WOLF_POWER 9
#define WOLF_INITIATIVE 5

Wolf::Wolf(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'W';
	this->initiative = WOLF_INITIATIVE;
	this->power = WOLF_POWER;
	this->name = "Wolf";
}

Wolf::Wolf(World* world, int born_day, int position, int power)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'W';
	this->initiative = WOLF_INITIATIVE;
	this->power = power;
	this->name = "Wolf";
}

Organism* Wolf::make_baby(int born_day, int position)
{
	Organism* new_organism = new Wolf (world, born_day, position);
	return new_organism;
}