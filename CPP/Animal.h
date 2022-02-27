#pragma once
#include "Organism.h"

class Animal : public Organism
{
public:
	int draw_place();
	void action() override;
	int collision(Organism* attacker) override;
};