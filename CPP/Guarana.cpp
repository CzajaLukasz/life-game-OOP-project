#include "Guarana.h"

#define GUARANA_POWER 0
#define GUARANA_INITIATIVE 0

Guarana::Guarana(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'G';
	this->initiative = GUARANA_INITIATIVE;
	this->power = GUARANA_POWER;
	this->name = "Guarana";
}

Organism* Guarana::make_baby(int born_day, int position)
{
	Organism* new_organism = new Guarana(world, born_day, position);
	return new_organism;
}

int Guarana::collision(Organism* attacker)
{
	attacker->set_power(attacker->get_power() + 3);
	cout << attacker->get_name() << " got 3 more power points because ";
	return Plant::collision(attacker);
}