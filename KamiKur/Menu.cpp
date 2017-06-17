#include "stdafx.h"
#include <SDL.h>
#include<SDL_ttf.h>
#include "stdlib.h"
#include <cstdio>
#include <ctime>
#include<string.h>
#include"Menu.h"


int GetButtonMM(int x, int y)
{
	for (int i = 0; i<4; i++)
	{
		if (x<500 && x>300 && y<140 + 80 * (i + 1) && y>140 + 80 * (i))
			return 3 - i;
	}
	return -1;
}
void DrawMM(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_Surface *surface[4];
	surface[0] = SDL_LoadBMP("quit.bmp");
	surface[1] = SDL_LoadBMP("continue.bmp");
	surface[2] = SDL_LoadBMP("score.bmp");
	surface[3] = SDL_LoadBMP("ng.bmp");
	SDL_Surface *MM = SDL_LoadBMP("mm_fon.bmp");
	SDL_Rect rect1 = { 0, 0, 800, 600 };
	SDL_SetColorKey(MM, SDL_TRUE, SDL_MapRGB(MM->format, 255, 255, 255));
	SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, MM);
	SDL_RenderCopy(renderer, texture1, NULL, &rect1);
	SDL_DestroyTexture(texture1);
	SDL_FreeSurface(MM);

	SDL_Rect rect = { 300, 0, 200, 80 };

	for (int i = 0; i < 4; i++)
	{
		rect.y = 412 - (5 * i + 80 * i);
		SDL_SetColorKey(surface[i], SDL_TRUE, SDL_MapRGB(surface[i]->format, 255, 255, 255));
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface[i]);
		SDL_RenderCopy(renderer, texture, NULL, &rect);

		SDL_DestroyTexture(texture);
	}

	SDL_RenderPresent(renderer);
	for (int i = 0; i < 4; i++)
		SDL_FreeSurface(surface[i]);
}

int MainMenu() {

	SDL_Window* window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	DrawMM(renderer);

	int choice = -1;

	do
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				choice = GetButtonMM(event.button.x, event.button.y);
			}
			else if (event.type == SDL_QUIT) choice = 0;
		}
	} while (choice == -1);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return choice;
}