#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
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
using namespace std;

int main()
{
	int height, width;
	cout << "Witaj w grze w zycie. Twoim celem jest unikanie pojedynkow z silniejszymi zwierzetami\n";
	cout << "i niewchodzenie w droge krwiozerczym roslinom. Staraj sie zbierac Guarany aby stac sie silniejszy\n";
	cout << "W kazdej rundzie musisz wybrac kierunek w ktorym chcesz podazyc (sterowanie strzalkami), a nastepnie gdy bedziesz\n";
	cout << "gotowy nacisnac 'n' aby rozpoczac kolejna runde. Twoja supermoca jest palenie sasiednich zwierzat i roslin\n";
	cout << "Aby ja uzyc nalezy nacisnac 'i' co spowoduje aktywacje supermocy na 5 rund (liczac od rundy w ktorej sie ja wlaczylo)\n";
	cout << "Gdy dzialanie supermocy sie skonczy pozostaje ona nieaktywna przez 5 kolejnych rund, wiec radze jej nie naduzywac :)\n";
	cout << "Gre mozna zakonczyc klikajac dwukrotnie 'x' zamiast 'n'\n\n";
	cout << "Aby rozpoczac gre nacisnij dowolny przycisk\n";
	char choose = _getch();
	system("cls");
	cout << "Jezeli chcesz wczytac gre z pliku wcisnij 'l', jezeli chcesz zaczac nowa gre wcisnij dowolny inny klawisz\n";
	choose = _getch();
	if (choose == 'l') 
	{ 
		fstream file;
		file.open("saved_game.txt", ios::in);
		if (file.good() == false)
		{
			system("cls");
			cout << "Zadna gra nie zostala zapisana";
			return 0;
		}
		string line;
		getline(file, line);
		height = atoi(line.c_str());
		getline(file, line);
		width = atoi(line.c_str());
	}
	else
	{
		system("cls");
		cout << "Podaj wysokosc mapy (minimalnie 10): ";
		cin >> height;
		cout << "Podaj szerokosc mapy (minimalnie 10): ";
		cin >> width;
		if (height < 10) { height = 10; }
		if (width < 10) { width = 10; }
	}
	World world(height, width);
	if (choose == 'l') 
	{
		world.load();
	}
	else
	{
		world.add_organism(new Wolf(&world, 0, 0), 0);
		world.add_organism(new Wolf(&world, 0, height / 10 * 0.3 * width), height / 10 * 0.3 * width);
		world.add_organism(new Wolf(&world, 0, height * width - 1), height * width - 1);
		world.add_organism(new Sheep(&world, 0, height / 10 * 0.9 * width), height / 10 * 0.9 * width);
		world.add_organism(new Sheep(&world, 0, height / 10 * 2.5 * width), height / 10 * 2.5 * width);
		world.add_organism(new Sheep(&world, 0, height / 10 * 2 * width - 1), height / 10 * 2 * width - 1);
		world.add_organism(new Grass(&world, 0, height / 10 * 3.2 * width), height / 10 * 3.2 * width);
		world.add_organism(new Grass(&world, 0, height / 10 * 5.6 * width), height / 10 * 5.6 * width);
		world.add_organism(new Grass(&world, 0, height / 10 * 8.4 * width), height / 10 * 8.4 * width);
		world.add_organism(new Fox(&world, 0, height / 10 * 3.4 * width), height / 10 * 3.4 * width);
		world.add_organism(new Fox(&world, 0, height / 10 * 7.2 * width), height / 10 * 7.2 * width);
		world.add_organism(new Fox(&world, 0, height / 10 * 5.8 * width), height / 10 * 5.8 * width);
		world.add_organism(new Turtle(&world, 0, height / 10 * 4.6 * width), height / 10 * 4.6 * width);
		world.add_organism(new Turtle(&world, 0, height / 10 * 8.6 * width), height / 10 * 8.6 * width);
		world.add_organism(new Turtle(&world, 0, height / 10 * 9.2 * width), height / 10 * 9.2 * width);
		world.add_organism(new Pine_Borscht(&world, 0, height / 10 * 1.4 * width), height / 10 * 1.4 * width);
		world.add_organism(new Pine_Borscht(&world, 0, height / 10 * 9 * width), height / 10 * 9 * width);
		world.add_organism(new Pine_Borscht(&world, 0, height / 10 * 2.8 * width), height / 10 * 2.8 * width);
		world.add_organism(new Guarana(&world, 0, height / 10 * 1.2 * width), height / 10 * 1.2 * width);
		world.add_organism(new Guarana(&world, 0, height / 10 * 3 * width), height / 10 * 3 * width);
		world.add_organism(new Guarana(&world, 0, height / 10 * 4.2 * width), height / 10 * 4.2 * width);
		world.add_organism(new Guarana(&world, 0, height / 10 * 6.6 * width), height / 10 * 6.6 * width);
		world.add_organism(new Dandelion(&world, 0, height / 10 * 7 * width), height / 10 * 7 * width);
		world.add_organism(new Dandelion(&world, 0, height / 10 * 8.8 * width), height / 10 * 8.8 * width);
		world.add_organism(new Berries(&world, 0, height / 10 * 6.8 * width), height / 10 * 6.8 * width);
		world.add_organism(new Berries(&world, 0, height / 10 * 7.6 * width), height / 10 * 7.6 * width);
		world.add_organism(new Berries(&world, 0, height / 10 * 9.8 * width), height / 10 * 9.8 * width);
		world.add_organism(new Antelope(&world, 0, height / 10 * 9.4 * width), height / 10 * 9.4 * width);
		world.add_organism(new Antelope(&world, 0, height / 10 * 0.6 * width), height / 10 * 0.6 * width);
		world.add_organism(new Antelope(&world, 0, height / 10 * 6.2 * width), height / 10 * 6.2 * width);
		world.add_organism(new Human(&world, 0, height / 10 * 5.5 * width), height / 10 * 5.5 * width);
	}
	char letter = ' ';
	while (true)
	{
		world.draw_world();
		world.do_round();
		while (letter != 'n') 
		{ 
			letter = _getch(); 
			if (letter == 's') 
			{ 
				world.save(); 
				world.draw_world();
				cout << "Gra zostala zapisana :)\nAby skonczyc gre wcisnij 'x', jezeli chcesz kontynuowac wcisnij 'n'";
				letter = _getch();
			}
			if (letter == 'x')
			{
				system("cls");
				cout << "Gra zostala zakonczona";
				return 0;
			}
		}
		letter = ' ';
	}
	return 0;
}