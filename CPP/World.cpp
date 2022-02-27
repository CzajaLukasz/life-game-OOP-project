#include "world.h"
#include "Fox.h"
#include "Antelope.h"
#include "Berries.h"
#include "Dandelion.h"
#include "Grass.h"
#include "Guarana.h"
#include "Pine_Borscht.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"
#include "Human.h"
#include <iostream>
//#include <cstdlib>
#include <string>

#define DIE 0
#define KILL 1
#define KILL_DIE 2
#define COME_BACK 3
#define EXCHANGE_PLACES 4
#define EMPTY -1
#define NONE -1
class Antelope;
using namespace std;

struct field
{
	bool empty = true;
	list<Organism*>::iterator organism;
};

World::World(int map_height, int map_width)
{
	this->map_height = map_height;
	this->map_width = map_width;
	this->day = 0;
	after_superpower = 10;
	map = new field[map_height * map_width];
	srand(time(NULL));
}

World::~World()
{
	delete[] map;
	for (list<Organism*>::iterator organism = organism_list.begin(); organism != organism_list.end(); organism++)
	{
		delete *organism;
	}
}

void World::save()
{
	fstream file;
	file.open("saved_game.txt", ios::out);
	file << map_height << endl << map_width << endl << day << endl;
	for (list<Organism*>::iterator organism = organism_list.begin(); organism != organism_list.end(); organism++)
	{ 
		file << (*organism)->get_name() << endl << (*organism)->get_position() << endl << (*organism)->get_born_day() << endl << (*organism)->get_power() << endl;
		if ((*organism)->get_name() == "Human") { file << after_superpower << endl; }
	}
	file.close();
}

void World::do_round()
{
	day++;
	for (list<Organism*>::iterator organism = organism_list.begin(); organism != organism_list.end(); organism++)
	{
		bool goback = false;
		if (goback) //gdy poprzednio zabito pierwszy organim to teraz trzeba sie cofnac  poniewaz wskazujemy na drugi organizm omijajac tego ktory byl drugi wczesniej
		{
			organism--;
			goback = false;
		}
		if ((*organism)->get_born_day() == day) { continue; }  //organizm nie rusza sie w turze w ktorej sie urodzil
		(*organism)->action();
		if ((*organism)->get_initiative() == -1) //jezeli organizm zginal
		{
			bool isfirst = false;
			list<Organism*>::iterator tmp = organism;
			if (organism != organism_list.begin()) { organism--; }
			else { isfirst = true; }
			delete_organism((*tmp)->get_position());
			if (isfirst)  //gdy organizm byl pierwszy
			{ 
				organism = organism_list.begin(); 
				goback = true;
			}
		}
	}
	if (after_superpower != 10) { after_superpower++; }
}

void World::draw_world()
{
	system("cls");
	cout << "Autor: Lukasz Czaja\nnr indeksu: 184249\n";
	cout << "Przebieg rundy:\n";
	cout << "(opcjonalne) Wlaczenie supermocy 'i' (jesli dostepna)\n1. Wybor ruchu (strzalki)\n2. Zapis gry 's' / Wyjscie z gry 'x' / Rozpoczecie nowej tury 'n'\n\n";
	cout << (char)201;  //ramka
	for (int i = 1; i <= map_width; i++) { cout << (char)205; }
	cout <<(char) 187<< "\n";
	for (int i = 0; i < map_height * map_width; i++) //rysowanie zwierzat
	{
		if (i % map_width == 0) { cout << (char) 186; }
		if (!map[i].empty) { (*map[i].organism)->draw(); }
		else { cout << " "; }

		if (i % map_width == map_width - 1) { cout << (char)186 << "\n"; }
	}
	cout << (char)200;   //ramka
	for (int i = 1; i <= map_width; i++) { cout << (char)205; }
	cout << (char)188 << "\n";
	cout << "Below you can see what changes will be made in the next round:\n";
}

void World::delete_organism(int position)
{
	map[position].empty = true;
	Organism* tmp = (*map[position].organism);
	organism_list.erase(map[position].organism);
	delete tmp;
}

void World::add_organism(Organism* organism, int position)
{
	cout << "There is a new " << organism->get_name() << " On the map\n";
	if (organism_list.empty())
	{
		organism_list.push_front(organism);
		map[position].organism = organism_list.begin();
		map[position].empty = false;
		return;
	}
	list<Organism*>::iterator tmp = organism_list.end();
	tmp--;
	if ((*tmp)->get_initiative() >= organism->get_initiative()) //jezeli inicjatywa ostatniego organizmu jest wieksza lub rowna to nowy organizm idzie na koniec
	{
		organism_list.push_back(organism);
		tmp++;
		map[position].organism = tmp;
		map[position].empty = false;
		return;
	}
	for (list<Organism*>::iterator iter = organism_list.begin(); iter != organism_list.end(); iter++)
	{
		if ((*iter)->get_initiative() < organism->get_initiative()) //dodanie organizmu przed pierwszym organizmem o nizszej inicjatywie
		{
			organism_list.insert(iter, organism);
			iter--;
			map[position].organism = iter;
			map[position].empty = false;
			break;
		}
	}
}



int World::free_field(int position)  //zwraca wolne sasiednie pole lub wartosc NONE gyd takiego pola nie ma
{
	if (position % map_width != 0 && map[position - 1].empty) { return position - 1; }
	if (position % map_width != map_width-1 && map[position + 1].empty) { return position + 1; }
	if (position >= map_width && map[position - map_width].empty) { return position - map_width; }
	if (position < (map_width*(map_height-1)) && map[position + map_width].empty) { return position + map_width; }
	return NONE;
}

 void World::wanted_move(int current_position, int wanted_position, char character) //funkcja decyduje o tym co sie wydarzy gdy organizm przesunie sie na zadane pole
{
	if (map[wanted_position].empty) 
	{ 
		move_organism(current_position, wanted_position); 
		return;
	}
	if (character == (*map[wanted_position].organism)->get_character()) //rozmnozenie
	{
		int free_field = this->free_field(wanted_position);
		if (free_field == NONE) { free_field = this->free_field(current_position); }
		if (free_field == NONE) { return; }
		this->add_organism((*map[current_position].organism)->make_baby(day, free_field), free_field);
		return;
	}
	int verdict = (*map[wanted_position].organism)->collision(*map[current_position].organism);
	if (verdict == KILL) //organizm atakujacy zabija organizm zajmujacy pole
	{
		if (map[wanted_position].empty)
		{
			move_organism(current_position, wanted_position);
			return;
		}
		delete_organism(wanted_position);
		move_organism(current_position, wanted_position);
		return;
	}
	else if (verdict == DIE) //organizm atakujacy umiera
	{
		(*map[current_position].organism)->set_initiative(-1);
		return;
	}
	else if (verdict == KILL_DIE) //umiera i zabija (zjedzenie trujacych roslin)
	{
		delete_organism(wanted_position);
		(*map[current_position].organism)->set_initiative(-1);
		return;
	}
	else if (verdict == EXCHANGE_PLACES) //zamiana miejsc (antylopa)
	{
		list<Organism*>::iterator tmp = map[wanted_position].organism;
		map[wanted_position].organism = map[current_position].organism;
		map[current_position].organism = tmp;
		(*map[current_position].organism)->set_position(current_position);
		(*map[wanted_position].organism)->set_position(wanted_position);
	}
}

void World::make_organism(string name, int position, int power, int born_day)
{
	Organism* organism;
	if (name == "Antelope") { organism = new Antelope(this, born_day, position, power); }
	else if (name == "Fox") { organism = new Fox(this, born_day, position, power); }
	else if (name == "Sheep") { organism = new Sheep(this, born_day, position, power); }
	else if (name == "Turtle") { organism = new Turtle(this, born_day, position, power); }
	else if (name == "Wolf") { organism = new Wolf(this, born_day, position, power); }
	else if (name == "Wolf Berries") { organism = new Berries(this, born_day, position); }
	else if (name == "Grass") { organism = new Grass(this, born_day, position); }
	else if (name == "Guarana") { organism = new Guarana(this, born_day, position); }
	else if (name == "Pine Borscht") { organism = new Pine_Borscht(this, born_day, position); }
	else if (name == "Dandelion") { organism = new Dandelion(this, born_day, position); }
	else { organism = new Dandelion(this, born_day, position); }
	add_organism(organism, position);
}

void World::load()
{
	fstream file;
	string line, name;
	int line_number = 0, position = 0, born_day = 0, power = 0, after_superpower = 0;
	file.open("saved_game.txt", ios::in);
	while (getline(file, line))
	{
		switch (line_number)
		{
		case 0: break;
		case 1: break;
		case 2: day = atoi(line.c_str()); break;
		case 3: name = line; break;
		case 4: position = atoi(line.c_str()); break;
		case 5: power = atoi(line.c_str()); break;
		case 6: born_day = atoi(line.c_str()); break;
		}
		if (name == "Human" && line_number == 6)
		{
			getline(file, line);
			after_superpower = atoi(line.c_str());
			add_organism(new Human(this, born_day, position, power, after_superpower), position);
			line_number = 2;
		}
		else if (line_number == 6)
		{
			make_organism(name, position, power, born_day);
			line_number = 2;
		}
		line_number++;
		}
	file.close();
}

void World::move_organism(int current_position, int wanted_position)
{
	(*map[current_position].organism)->set_position(wanted_position);
	map[wanted_position].empty = false;
	map[wanted_position].organism = map[current_position].organism;
	map[current_position].empty = true;
}

int World::is_free(int position)  //sprawdza czy pole jest wolne, jesli nie to zwraca si³ê organizmu na polu
{
	if (map[position].empty) { return EMPTY; }
	return (*map[position].organism)->get_power();
}

string World::get_pos_organism_name(int position)
{
	return (*map[position].organism)->get_name();
}

int World::get_map_width()
{
	return map_width;
}

int World::get_map_height()
{
	return map_height;
}

int World::get_day()
{
	return day;
}

void World::set_after_superpower(int after_superpower)
{
	this->after_superpower = after_superpower;
}

