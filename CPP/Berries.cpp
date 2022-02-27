#include "Berries.h"

#define BERRIES_POWER 99
#define BERRIES_INITIATIVE 0
#define KILL_DIE 2

Berries::Berries(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'B';
	this->initiative = BERRIES_INITIATIVE;
	this->power = BERRIES_POWER;
	this->name = "Wolf Berries";
}

Organism* Berries::make_baby(int born_day, int position)
{
	Organism* new_organism = new Berries(world, born_day, position);
	return new_organism;
}

int Berries::collision(Organism* attacker) //jagoda umiera poniewaz jest jedzona ale zabija organizm ktory ja zjadl
{
	cout << attacker->get_name() << " ate " << this->get_name() << " and died \n";
	return KILL_DIE;
}