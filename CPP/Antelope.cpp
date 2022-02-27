#include "Antelope.h"

#define ANTELOPE_POWER 4
#define ANTELOPE_INITIATIVE 4
#define DIRECTIONS 4
#define KILL 1
#define NONE -1
#define EXCHANGE_PLACES 4

Antelope::Antelope(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'A';
	this->initiative = ANTELOPE_INITIATIVE;
	this->power = ANTELOPE_POWER;
	this->name = "Antelope";
}
Antelope::Antelope(World* world, int born_day, int position, int power)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'A';
	this->initiative = ANTELOPE_INITIATIVE;
	this->power = power;
	this->name = "Antelope";
}

int Antelope::draw_place()
{
	int first_draw = Animal::draw_place(); // losowanie dowolnego sasiedniego miejsca
	int directions[DIRECTIONS];
	directions[0] = first_draw;
	int available_directions = 1;
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();
	
	//losowanie z miejsc sasiadujacych z wylosowanym wlacznie z wylosowanym, wylaczajac miejsce na ktorym jestesmy
	if (first_draw % map_width != 0 && first_draw-1 !=position)
	{
		directions[available_directions] = first_draw - 1;
		available_directions++;
	}
	if (first_draw % map_width != map_width - 1 && first_draw + 1 != position)
	{
		directions[available_directions] = first_draw + 1;
		available_directions++;
	}
	if (first_draw >= map_width && first_draw - map_width != position)
	{
		directions[available_directions] = first_draw - map_width;
		available_directions++;
	}
	if (first_draw < (map_width * (map_height - 1)) && first_draw + map_width != position)
	{
		directions[available_directions] = first_draw + map_width;
		available_directions++;
	}
	return directions[rand() % available_directions];
}

void Antelope::action()
{
	int wanted_position = draw_place();
	world->wanted_move(this->position, wanted_position, this->character);
}

int Antelope::collision(Organism* attacker)
{
	if (rand() % 2) { return Animal::collision(attacker); }
	int free_field = world->free_field(position);
	if (free_field == NONE) //jezeli antylopa nie ma miejsca do ucieczki to wchodzi na miejsce atakujacego
	{ 
		cout << attacker->get_name() << " changed place with " << this->get_name()<<"\n";
		return EXCHANGE_PLACES; 
	} 
	world->move_organism(position, free_field);
	return KILL;
}

Organism* Antelope::make_baby(int born_day, int position)
{
	Organism* new_organism = new Antelope(world, born_day, position);
	return new_organism;
}