// KamiKur.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <SDL.h>
#include<SDL_ttf.h>
#include "stdlib.h"
#include <cstdio>
#include <ctime>
#include<string.h>
#include "Menu.h"
#include "Gay.h"
#include"Records.h"

void _tmain(int argc, char **argv)
{

	system("chcp 1251");
	SDL_Init(SDL_INIT_EVERYTHING);

	int choice;

	do
	{
		choice = MainMenu();

		switch (choice)
		{
		case 3: //new game
				choice = NewGame();
			break;
		case 2: //score
				choice = Score();
			break;
		case 1: //continue
			choice = MLoad();
			break;
		default: break;
		}
	} while (choice != 0);

	SDL_Quit();
 
}

