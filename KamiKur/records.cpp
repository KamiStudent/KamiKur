
#include "stdafx.h"
#include <SDL.h>
#include<SDL_ttf.h>
#include "stdlib.h"
#include "Records.h"

int Score() {
	SDL_Window* window = SDL_CreateWindow("score", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;

	DrawBack(renderer);
	LoadRecords(renderer);
	SDL_RenderPresent(renderer);
	bool q = false;
	do
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.x > 247 && event.button.x < 333 && event.button.y > 342 && event.button.y < 373)
					q = true;
			}
			else if (event.type == SDL_QUIT) q = true;
		}
	} while (!q);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return -1;
}

void DrawBack(SDL_Renderer * ren) {
	SDL_Surface *sc = SDL_LoadBMP("table.bmp");
	SDL_Rect rect1 = { 0, 0, 600, 400 };
	SDL_SetColorKey(sc, SDL_TRUE, SDL_MapRGB(sc->format, 255, 255, 255));
	SDL_Texture *texture1 = SDL_CreateTextureFromSurface(ren, sc);
	SDL_RenderCopy(ren, texture1, NULL, &rect1);
	SDL_DestroyTexture(texture1);
	SDL_FreeSurface(sc);
}

void DrawScore(SDL_Renderer *rend, int i, int score) {
	char text[10];
	TTF_Init();
	TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
	SDL_Color fore_color = { 63,72,204 };
	SDL_Color back_color = { 255,255,255 };
	SDL_Surface* textSurface = NULL;
	sprintf(text, "%d", score);
	textSurface = TTF_RenderText_Shaded(my_font, text, fore_color, back_color);
	SDL_Rect rect;
	if ((i % 2) > 0) {
		rect = { 150,20 * i + 100,50,20 };
	}
	else rect = { 300,20 * i + 80,50,20 };
	SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, textSurface);
	SDL_RenderCopy(rend, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textSurface);
	TTF_Quit();
}

void InRecords(int sc) {
	FILE * fd;
	int curr, A[10];
	fopen_s(&fd, "score.txt", "rt");
	fseek(fd, 0, SEEK_END);
	long pos = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	if (pos > 0)
	{
		for (int i = 0; i < 10; i++)
		{
			fscanf(fd, "%d", &curr);
			if (curr < sc) A[i] = sc;
			else A[i] = curr;
		}
	}
	fclose(fd);

	fopen_s(&fd, "score.txt", "w");

	for (int i = 0; i < 10; i++)
	{
		fprintf(fd, "%d ", A[i]);
	}

	fclose(fd);
}
//добавление в табличку
void LoadRecords(SDL_Renderer *rend) {
	FILE * fd;
	int curr;
	fopen_s(&fd, "score.txt", "r");

	for (int i = 1; i <= 10; i++)
	{
		fscanf(fd, "%d", &curr);
		DrawScore(rend, i, curr);

	}
	fclose(fd);

};// подгрузка из файла и отрисовка