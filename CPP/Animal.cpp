#include "Animal.h"

#define DIRECTIONS 4
#define DIE 0
#define KILL 1

int Animal::draw_place() //losowanie miejsca do ruchu z dostepnych miejsc
{
	int available_directions = 0;
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();
	int directions[DIRECTIONS];

	if (position % map_width != 0)  //jezeli nie lewa krawedz
	{
		directions[available_directions] = position - 1;
		available_directions++;
	}
	if (position % map_width != map_width - 1) // jezeli nie prawa krawedz
	{
		directions[available_directions] = position + 1;
		available_directions++;
	}
	if (position >= map_width) // jezeli nie gorna krawedz
	{
		directions[available_directions] = position - map_width;
		available_directions++;
	}
	if (position < (map_width * (map_height - 1))) // jezeli nie dolna krawedz
	{
		directions[available_directions] = position + map_width;
		available_directions++;
	}
	return directions[rand() % available_directions];
}

void Animal::action()
{
	int wanted_position = draw_place();
	world->wanted_move(this->position, wanted_position, this->character);
}

int Animal::collision(Organism* attacker)
{
	if (attacker->get_power() > this->get_power()) 
	{ 
		cout << attacker->get_name() << " killed " << this->get_name()<<"\n";
		return KILL; 
	}
	if (attacker->get_power() < this->get_power()) 
	{ 
		cout << this->get_name() << " killed " << attacker->get_name() << "\n";
		return DIE;
	}
	if (attacker->get_born_day() > this->get_born_day()) 
	{ 
		cout << this->get_name() << " killed " << attacker->get_name() << "\n";
		return DIE;
	}
	cout << attacker->get_name() << " killed " << this->get_name() << "\n";
	return KILL;
}