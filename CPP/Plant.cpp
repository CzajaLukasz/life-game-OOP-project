#include "Plant.h"
#define DIRECTIONS 4
#define NONE -1
#define KILL 1
#define FREE -1

bool Plant::sow()  //losowanie czy zasiac rosline
{
	int random = rand() % 100;
	if (random % 7 == 0) { return true; } //co 7 raz uda sie rozmnozyc
	return false;
}

int Plant::draw_place()
{
	int available_directions = 0;
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();
	int directions[DIRECTIONS];
	//losowanie z miejsc ktore sa wolne
	if (position % map_width != 0 && world->is_free(position-1) == FREE)
	{
		directions[available_directions] = position - 1;
		available_directions++;
	}
	if (position % map_width != map_width - 1 && world->is_free(position + 1) == FREE)
	{
		directions[available_directions] = position + 1;
		available_directions++;
	}
	if (position >= map_width && world->is_free(position - map_width) == FREE)
	{
		directions[available_directions] = position - map_width;
		available_directions++;
	}
	if (position < (map_width * (map_height - 1)) && world->is_free(position + map_width) == FREE)
	{
		directions[available_directions] = position + map_width;
		available_directions++;
	}
	if (available_directions == 0) { return NONE; }
	return directions[rand() % available_directions];
}

void Plant::action()
{
	if (!sow()) { return; }
	int wanted_position = draw_place();
	if (wanted_position == NONE) { return; }
	world->add_organism(this->make_baby(world->get_day(), wanted_position), wanted_position);
}

int Plant::collision(Organism* attacker)  //roslina zawsze umiera poniewaz jest jedzona
{
	cout << attacker->get_name() << " ate " << this->get_name()<<"\n";
	return KILL;
}