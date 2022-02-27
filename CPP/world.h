#pragma once
#include <list>
#include <cstdlib>
#include <fstream>
#include "Organism.h"

using namespace std;

struct field;
class Organism;

using namespace std;

class World
{
private:
	list<Organism*> organism_list;
	int map_width;
	int map_height;
	int day;
	int after_superpower;
	field* map;
public:
	World(int map_height, int map_width);
	~World();
	void save();
	void do_round();
	void draw_world();
	void delete_organism(int position);
	void add_organism(Organism* organism, int position);
	int free_field(int position);
	void wanted_move(int current_position, int wanted_position, char character);
	void make_organism(string name, int position, int power, int born_day);
	void load();
	void move_organism(int current_position, int wanted_position);
	int is_free(int position);
	string get_pos_organism_name(int position);
	int get_map_width();
	int get_map_height();
	int get_day();
	void set_after_superpower(int after_superpower);
};