#include "Organism.h"

using namespace std;

void Organism::draw()
{
	cout << character;
}

int Organism::get_initiative()
{
	return initiative;
}

int Organism::get_power()
{
	return power;
}

int Organism::get_position()
{
	return position;
}

char Organism::get_character()
{
	return character;
}

int Organism::get_born_day()
{
	return born_day;
}

string Organism::get_name()
{
	return name;
}

void Organism::set_position(int position)
{
	this->position = position;
}

void Organism::set_power(int power)
{
	this->power = power;
}

void Organism::set_initiative(int initiative)
{
	this->initiative = initiative;
}
