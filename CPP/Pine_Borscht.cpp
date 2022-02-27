#include "Pine_Borscht.h"

#define BORSCHT_POWER 10
#define BORSCHT_INITIATIVE 0
#define KILL_DIE 2
#define EMPTY -1
#define PLANT 0

Pine_Borscht::Pine_Borscht(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'P';
	this->initiative = BORSCHT_INITIATIVE;
	this->power = BORSCHT_POWER;
	this->name = "Pine Borscht";
}

int Pine_Borscht::collision(Organism* attacker) //ginie i zabija tak samo jak jagoda
{
	cout << attacker->get_name() << " ate " << this->get_name() << " and died \n";
	return KILL_DIE;
}

void Pine_Borscht::action()
{
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();

	if (position % map_width != 0 && world->is_free(position-1) > PLANT)
	{
		if (world->get_pos_organism_name(position - 1) != "Pine Borscht" && world->get_pos_organism_name(position - 1) != "Wolf Berries")
		{
			cout << this->get_name() << " killed " << world->get_pos_organism_name(position - 1) << "\n";
			world->delete_organism(position - 1);
		}
	}
	if (position % map_width != map_width - 1 && world->is_free(position + 1) > PLANT)
	{
		if (world->get_pos_organism_name(position + 1) != "Pine Borscht" && world->get_pos_organism_name(position + 1) != "Wolf Berries")
		{
			cout << this->get_name() << " killed " << world->get_pos_organism_name(position + 1) << "\n";
			world->delete_organism(position + 1);
		}
	}
	if (position >= map_width && world->is_free(position - map_width) > PLANT)
	{
		if (world->get_pos_organism_name(position - map_width) != "Pine Borscht" && world->get_pos_organism_name(position - map_width) != "Wolf Berries")
		{
			cout << this->get_name() << " killed " << world->get_pos_organism_name(position - map_width) << "\n";
			world->delete_organism(position - map_width);
		}
	}
	if (position < (map_width * (map_height - 1)) && world->is_free(position + map_width) > PLANT)
	{
		if (world->get_pos_organism_name(position + map_width) != "Pine Borscht" && world->get_pos_organism_name(position + map_width) != "Wolf Berries")
		{
			cout << this->get_name() << " killed " << world->get_pos_organism_name(position + map_width) << "\n";
			world->delete_organism(position + map_width);
		}
	}
	Plant::action();
}

Organism* Pine_Borscht::make_baby(int born_day, int position)
{
	Organism* new_organism = new Pine_Borscht(world, born_day, position);
	return new_organism;
}