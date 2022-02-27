#pragma once
#include "Animal.h"

class Human : public Animal
{
private:
	int after_superpower; //ilosc dni po uzyciu super mocy
public:
	Human(World* world, int born_day, int position);
	Human(World* world, int born_day, int position, int power, int after_superpower);
	void kill_neighbors();
	int draw_place();
	void action() override;
	Organism* make_baby(int born_day, int position) override;
	int get_after_superpower();
};