#include "Fox.h"

#define FOX_POWER 3
#define FOX_INITIATIVE 7
#define DIRECTIONS 4
#define NONE -1

Fox::Fox(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'F';
	this->initiative = FOX_INITIATIVE;
	this->power = FOX_POWER;
	this->name = "Fox";
}

Fox::Fox(World* world, int born_day, int position, int power)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'F';
	this->initiative = FOX_INITIATIVE;
	this->power = power;
	this->name = "Fox";
}

int Fox::draw_place() //lis losuje miejsce z tych ktore sa wolne, lub zajmowane przez slabsze organizmy. Jezeli nie ma takiego miejsca to sie nie rusza
{
	int available_directions = 0;
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();
	int directions[DIRECTIONS];

	if (position % map_width != 0 && world->is_free(position - 1) <= this->power)
	{
		directions[available_directions] = position - 1;
		available_directions++;
	}
	if (position % map_width != map_width - 1 && world->is_free(position + 1) <= this->power)
	{
		directions[available_directions] = position + 1;
		available_directions++;
	}
	if (position >= map_width && world->is_free(position - map_width) <= this->power)
	{
		directions[available_directions] = position - map_width;
		available_directions++;
	}
	if (position < (map_width * (map_height - 1)) && world->is_free(position + map_width) <= this->power)
	{
		directions[available_directions] = position + map_width;
		available_directions++;
	}
	if (available_directions == 0) { return NONE; }
	return directions[rand() % available_directions];
}

void Fox::action()
{
	int wanted_position = draw_place();
	if (wanted_position == NONE) { return; }
	world->wanted_move(this->position, wanted_position, this->character);
}

Organism* Fox::make_baby(int born_day, int position)
{
	Organism* new_organism = new Fox(world, born_day, position);
	return new_organism;
}