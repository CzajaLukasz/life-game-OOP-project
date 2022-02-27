#pragma once
#include "Organism.h"

class Plant : public Organism
{
public:
	static bool sow();
	int draw_place();
	void action() override;
	int collision(Organism* attacker) override;
};