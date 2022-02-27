#include <conio.h>
#include "Human.h"

#define HUMAN_POWER 5
#define HUMAN_INITIATIVE 4
#define EMPTY -1

Human::Human(World* world, int born_day, int position)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'H';
	this->initiative = HUMAN_INITIATIVE;
	this->power = HUMAN_POWER;
	this->after_superpower = 10;
	this->name = "Human";
}

Human::Human(World* world, int born_day, int position, int power, int after_superpower)
{
	this->world = world;
	this->position = position;
	this->born_day = born_day;
	this->character = 'H';
	this->initiative = HUMAN_INITIATIVE;
	this->power = power;
	this->after_superpower = after_superpower;
	this->name = "Human";
}

void Human::kill_neighbors()
{
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();
	if (position % map_width != 0 && world->is_free(position - 1) != EMPTY)
	{
		cout << this->get_name() << " burned " << world->get_pos_organism_name(position - 1) << "\n";
		world->delete_organism(position - 1);
	}
	if (position % map_width != map_width - 1 && world->is_free(position + 1) != EMPTY)
	{
		cout << this->get_name() << " burned " << world->get_pos_organism_name(position + 1) << "\n";
		world->delete_organism(position + 1);
	}
	if (position >= map_width && world->is_free(position - map_width) != EMPTY)
	{
		cout << this->get_name() << " burned " << world->get_pos_organism_name(position - map_width) << "\n";
		world->delete_organism(position - map_width);
	}
	if (position < (map_width * (map_height - 1)) && world->is_free(position + map_width) != EMPTY)
	{
		cout << this->get_name() << " burned " << world->get_pos_organism_name(position + map_width) << "\n";
		world->delete_organism(position + map_width);
	}
}

int Human::draw_place()
{
	int choosen_position=-1;
	int map_width = world->get_map_width();
	int map_height = world->get_map_height();

	while (choosen_position == -1)
	{
		 char char1 = _getch();
		 if (char1 == 'i' && after_superpower == 10)
		 {
			 after_superpower = 0;
			 world->set_after_superpower(0);
			 cout << "Superpower turned on\n";
		 }
		if (char1 == 0 || char1==0xE0 || char1==-32) {
			switch (_getch()) {
			case 72: //strzalka w gore
				if (position > map_width) { choosen_position = position - map_width; }
				break;
			case 80: //strzalka w dol
				if (position < (map_width* (map_height - 1))) { choosen_position = position + map_width; }
				break;
			case 77: //w prawo
				if (position % map_width != map_width-1) { choosen_position = position + 1; }
				break;
			case 75: //w lewo
				if (position % map_width != 0) { choosen_position = position - 1; }
				break;
			}
		}
	}
	if (after_superpower < 5) //spalanie wszystkich sasiednich organizmow przez 5 rund ( od rundy 0 do rundy 4)
	{
		kill_neighbors();
	}
	else if (after_superpower < 10) 
	{
		after_superpower++; 
		if (after_superpower == 10) { cout << "Superpower available again\n"; }
	}
	return choosen_position;
}

void Human::action()
{
	int wanted_position = draw_place();
	world->wanted_move(this->position, wanted_position, this->character);
	if (after_superpower < 5) //ponowne spalanie organizmow na nowe pozycji
	{
		kill_neighbors();
		after_superpower++;
		if (after_superpower == 5) { cout << "Superpower turned off\n"; }
	}
}

Organism* Human::make_baby(int born_day, int position)
{
	Organism* new_organism = new Human(world, born_day, position);
	return new_organism;
}

int Human::get_after_superpower()
{
	return after_superpower;
}