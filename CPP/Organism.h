#pragma once
#include <iostream>
#include "world.h"
class World;

using namespace std;

class Organism
{
protected:
	World* world;
	int born_day;
	int power;
	int position;
	char character;
	int initiative;
	string name;
public:
	virtual void action() = 0;
	virtual int collision(Organism* attacker) = 0;
	void draw();
	int get_initiative();
	int get_power();
	int get_position();
	char get_character();
	int get_born_day();
	string get_name();
	void set_position(int position);
	void set_power(int power);
	void set_initiative(int initiative);
	virtual Organism* make_baby(int born_day, int position) = 0;
};