#include "Turtle.h"

#define TURTLE_POWER 2
#define TURTLE_INITIATIVE 1
#define MAX_HOLD_POWER 5
#define COME_BACK 3

Turtle::Turtle(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'T';
	this->initiative = TURTLE_INITIATIVE;
	this->power = TURTLE_POWER;
	this->name = "Turtle";
}

Turtle::Turtle(World* world, int born_day, int position, int power)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'T';
	this->initiative = TURTLE_INITIATIVE;
	this->power = power;
	this->name = "Turtle";
}

void Turtle::action()
{
	if (rand() % 4) { return; }
	Animal::action();
}

int Turtle::collision(Organism* attacker)
{
	if (attacker->get_power() < MAX_HOLD_POWER) 
	{ 
		cout << this->get_name() << " countered attack from " << attacker->get_name() << "\n";
		return COME_BACK; 
	}
	return Animal::collision(attacker);
}

Organism* Turtle::make_baby(int born_day, int position)
{
	Organism* new_organism = new Turtle(world, born_day, position);
	return new_organism;
}