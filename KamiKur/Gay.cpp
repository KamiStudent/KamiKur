#include "stdafx.h"
#include <SDL.h>
#include<SDL_ttf.h>
#include "stdlib.h"
#include <cstdio>
#include <ctime>
#include<string.h>
#include "Gay.h"
#include"Records.h"


struct Car {
	int coordX;
	int coordY;
	int bonus;
	int speed;
};

struct Ball {
	int CoordX;
	int CoordY;
	int vx;
	int vy;
	int naprx;
	int napry;
};

Car car{ 15,578,0,150 };
Ball ball{ 15,563,4,12,-1,-1 };
int **Cart = NULL;
bool lost = false;
bool quit = false;
int Life = 3;
int W = 800, H = 600;
int score = 0;
int lvl = 1;
SDL_Surface *back = NULL;
SDL_Surface* cars = NULL;
SDL_Texture *cart = NULL;
SDL_Surface* balls = NULL;
SDL_Texture *ballt = NULL;
SDL_Texture *backt = NULL;
SDL_Surface* block[5];
void CarMove(int click) {
	if (click != 0)
	{
		if (click < 0 && car.coordX > 0)
		{
			car.coordX -= 10;
		}
		else if (click > 0 && car.coordX+65 < 736) { car.coordX += 10; }
	}
};
void InitGame(SDL_Renderer* renderer) {

	Cart = (int**)calloc(6, sizeof(int*));
	for (int i = 0; i < 6; i++)
		Cart[i] = (int*)calloc(13, sizeof(int));

	back = SDL_LoadBMP("background.bmp");
	backt = SDL_CreateTextureFromSurface(renderer, back);
	cars = SDL_LoadBMP("2.bmp");
	SDL_SetColorKey(cars, SDL_TRUE, SDL_MapRGB(cars->format, 255, 255, 255));
	cart = SDL_CreateTextureFromSurface(renderer, cars);
	balls = SDL_LoadBMP("ball.bmp");
	SDL_SetColorKey(balls, SDL_TRUE, SDL_MapRGB(balls->format, 255, 255, 255));
	ballt = SDL_CreateTextureFromSurface(renderer, balls);
	block[0] = SDL_LoadBMP("block1.bmp");
	block[1] = SDL_LoadBMP("block2.bmp");
	block[2] = SDL_LoadBMP("block3.bmp");
	block[3] = SDL_LoadBMP("block4.bmp");
	block[4] = SDL_LoadBMP("block5.bmp");
}
void FreeGame() {
	SDL_FreeSurface(back);
	SDL_FreeSurface(cars);
	SDL_FreeSurface(balls);
	for (int k = 0; k < 4; k++)
	{
		SDL_FreeSurface(block[k]);
	}
	SDL_DestroyTexture(backt);
	SDL_DestroyTexture(cart);
	SDL_DestroyTexture(ballt);
}
void background(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, backt, NULL, NULL);
};

void DrawCar(SDL_Renderer *renderer) {
	SDL_Rect Dest{ 0,0,125,22 };
	Dest.x = car.coordX;
	Dest.y = car.coordY;
	SDL_RenderCopy(renderer, cart, NULL, &Dest);

};

void DrawBall(SDL_Renderer *renderer) {

	SDL_Rect Dest{ ball.CoordX-15,ball.CoordY-15,34,34 };
	SDL_RenderCopy(renderer, ballt, NULL, &Dest);

};

void Win() {
	SDL_Window* winwin = SDL_CreateWindow("Win", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(winwin, -1, 0);
	SDL_Surface* win = SDL_LoadBMP("Win.bmp");
	SDL_SetColorKey(win, SDL_TRUE, SDL_MapRGB(win->format, 255, 255, 255));
	SDL_Texture *wint = SDL_CreateTextureFromSurface(renderer, win);
	SDL_RenderCopy(renderer, wint, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	SDL_DestroyTexture(wint);
	SDL_FreeSurface(win);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(winwin);

};

void Lose() {
	SDL_Window* loselose = SDL_CreateWindow("Lose", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(loselose, -1, 0);
	SDL_Surface* lose = SDL_LoadBMP("Lose.bmp");
	SDL_SetColorKey(lose, SDL_TRUE, SDL_MapRGB(lose->format, 255, 255, 255));
	SDL_Texture *loset = SDL_CreateTextureFromSurface(renderer, lose);
	SDL_RenderCopy(renderer, loset, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	SDL_DestroyTexture(loset);
	SDL_FreeSurface(lose);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(loselose);
}
int bonus = 0;
int BonusBl() {
	srand(time(NULL));
	int mbonus = rand() % 100;
	if (mbonus > 80) return(rand() % 8 + 1);
	else return 0;
};
void BonusSpeed(int a, int b) {
	if (a == 0) {
		if (b < 0) { ball.vx -= 3; ball.vy -= 3; }
		else { ball.vx += 3; ball.vy += 3;
		}
	}
	else {
		if (b < 0) car.speed -= 3;
		else car.speed += 3;
	}

}


void Bonus() {
	switch (bonus)
	{
	case 1: {Life++; break; }
	case 2: {srand(time(NULL));
		int a = rand() % 80 + 20;
		score += a; break; }
	case 4: {Life--; break; }
	case 5: {BonusSpeed(0, 1); break; }
	case 6: {BonusSpeed(0, -1); break; }
	case 7: {BonusSpeed(1, 1); break; }
	case 8: {BonusSpeed(1, -1); break; }
	default: break;
	}
}
bool win = true;

bool CollideX( int L, int P ) {
	if (ball.CoordX - 15 >= L && ball.CoordX + 15 <= P) return 1;
//	if (ball.CoordX - 15 + step >= L && ball.CoordX + 15 + step <= P) return 1;
	return 0;
}

bool CollideY( int V, int N) {
	if (ball.CoordY - 15 >= V && ball.CoordY + 15 <= N) return 1;
//	if (debug) print "не попали в...."
//	if (ball.CoordY - 15 + step >= V && ball.CoordY + 15 + step <= N) return 1;
	return 0;
}

int MirrorX(int xn,int xk,int yn, int yk, int y){//

return ((y-yn)*(xk-xn)/(yk-yn)+xn);
}

int MirrorY(int xn, int xk, int x, int yn, int yk){

return ((x-xn)*(yk-yn)/(yk-yn)+yn);
}
// ïåðåïèñàòü
void BlockBall()
{
	win = true;
	bool bon = false;
	int stx = ball.naprx*ball.vx;
	int sty = ball.napry*ball.vy;
	int L;//Lev
	int N;//Niz
	int V;//verx
	int P;// prav
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			V = i * 30 + 100;
			N = (i + 1) * 30 + 100;
			L = j * 60 + 10;
			P = (j+1) * 60 + 10;
			if (Cart[i][j] > 0) {
				win = false;

				if(CollideX(L,P)){
                    if(ball.naprx>0) ball.CoordX-=MirrorX(ball.CoordX-stx,ball.CoordX,ball.CoordY-sty,ball.CoordY,L);
                    else ball.CoordX-=MirrorX(ball.CoordX-stx,ball.CoordX,ball.CoordY-sty,ball.CoordY,P);

				ball.naprx*=-1;
				Cart[i][j]--;
                score += 10;
                if (Cart[i][j] == 0) bon = true;
				}
                if (CollideY(V,N)){
                    if (ball.napry>0) ball.CoordY-=MirrorY(ball.CoordX-stx,ball.CoordX,V,ball.CoordY-sty,ball.CoordY);
                    else ball.CoordY-=MirrorY(ball.CoordX-stx,ball.CoordX,N,ball.CoordY-sty,ball.CoordY);
                    ball.napry*=-1;
                    Cart[i][j]--;
                    score += 10;
                    if (Cart[i][j] == 0) bon = true;
                }

            }
            if (bon) bonus = BonusBl();
        }
    }
}

	bool CarBall() {
		if (ball.napry > 0) {
			if (ball.CoordX-15 > car.coordX && ball.CoordX+15 < car.coordX + 125)
			{
				ball.napry *= -1;
				return false;
			}
		}
		else return true;
	}


	void MoveBall()
	{

		int flag = 0;

		if (ball.CoordX == 15 && ball.naprx < 0) //êîîðäÕ-ðàäèóñ
		{
			ball.naprx *= -1;
		}
		else if (ball.CoordX + ball.naprx*ball.vx <= 15)
		{
			ball.CoordX = 15; flag = 1;
		}

		if (ball.CoordX + 15 == W&& ball.naprx > 0)
		{
			ball.naprx *= -1;
		}
		else if (ball.CoordX + 15 + ball.naprx*ball.vx >= W)
		{
			ball.CoordX = W - 15; flag = 1;
		}


		if (ball.CoordY == 15 && ball.napry < 0)
		{
			ball.napry *= -1;
		}
		else if (ball.CoordY + ball.napry*ball.vy <= 15)
		{
			ball.CoordY = 15; flag = 2;
		}

		BlockBall();
		Bonus();
		if (ball.CoordY + 37 > H)
		{/*
			if (CarBall()) {
				Life--;
				lost = true;
				if (Life == 0) {
					Lose();
					quit = true;
				}*/
				ball.napry *= -1;
			//}
		}
		//Âûøå îïèñàíî ïîâåäåíèå ìÿ÷èêà ïðè ñòîëêíîâåíèè ñî ñòåíêàìè
		if (flag != 1)
		{
			ball.CoordX += ball.naprx*ball.vx;
		}
		if (flag != 2)
		{
			ball.CoordY += ball.napry*ball.vy;
		}
	}
	void ReadCart() {

		FILE *fd;
		switch (lvl) {

		case 1: {fopen_s(&fd, "cart1.txt", "r"); break; }
		case 2: {fopen_s(&fd, "cart2.txt", "r"); break; }
		case 3: {fopen_s(&fd, "cart3.txt", "r"); break; }
		case 4: {fopen_s(&fd, "cart4.txt", "r"); break; }
		case 5: {fopen_s(&fd, "cart5.txt", "r"); break; }
		}
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				fscanf_s(fd, "%d", &Cart[i][j]);
			}
		}
		fclose(fd);
	}



	void DrawnBlock(SDL_Renderer *rend, int i, int j) {
		SDL_Rect rect = { 10 + j * 60, 100 + i * 30, 60, 30 };
		SDL_Texture *blockt = SDL_CreateTextureFromSurface(rend, block[Cart[i][j] - 1]);
		SDL_RenderCopy(rend, blockt, NULL, &rect);
		SDL_DestroyTexture(blockt);
	}
	void DrawCart(SDL_Renderer *rend) {

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (Cart[i][j] > 0)
				{
					DrawnBlock(rend, i, j);
				}
			}
		}
	}


	void DrawScore(SDL_Renderer *rend) {
		char text[10];
		TTF_Init();
		TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
		SDL_Color fore_color = { 63,72,204 };
		SDL_Color back_color = { 255,255,255 };
		SDL_Surface* textSurface = NULL;
		sprintf(text, "%d", score);
		//_itoa_s(score, text, 10);//
		textSurface = TTF_RenderText_Shaded(my_font, text, fore_color, back_color);
		SDL_Rect rect = { 894,25, 40, 50 };
		SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, textSurface);
		SDL_RenderCopy(rend, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(textSurface);
		TTF_Quit();
	}

	void DrawLife(SDL_Renderer *rend) {
		char text[2];
		TTF_Init();
		TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
		SDL_Color fore_color = { 63,72,204 };
		SDL_Color back_color = { 255,255,255 };
		SDL_Surface* textSurface = NULL;
		_itoa_s(Life, text, 20);
		textSurface = TTF_RenderText_Shaded(my_font, text, fore_color, back_color);
		SDL_Rect rect = { 910,111, 20, 50 };
		SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, textSurface);
		SDL_RenderCopy(rend, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(textSurface);
		TTF_Quit();
	}

	void DrawLvl(SDL_Renderer *rend) {
		char text[2];
		TTF_Init();
		TTF_Font* my_font = TTF_OpenFont("font.ttf", 100);
		SDL_Color fore_color = { 63,72,204 };
		SDL_Color back_color = { 255,255,255 };
		SDL_Surface* textSurface = NULL;
		_itoa_s(lvl, text, 20);
		textSurface = TTF_RenderText_Shaded(my_font, text, fore_color, back_color);
		SDL_Rect rect = { 942,203, 20, 50 };
		SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, textSurface);
		SDL_RenderCopy(rend, texture, NULL, &rect);

		TTF_Quit();
	}

	void DrawBonus(SDL_Renderer *rend) {
		SDL_Surface* bon;
		switch (bonus)
		{
		case 1: {bon = SDL_LoadBMP("bonus1.bmp"); break; }
		case 2: {bon = SDL_LoadBMP("bonus2.bmp"); break; }
				//case 3: {bon = SDL_LoadBMP("bonus3.bmp"); break; }
		case 4: {bon = SDL_LoadBMP("bonus4.bmp"); break; }
		case 5: {bon = SDL_LoadBMP("bonus5.bmp"); break; }
		case 6: {bon = SDL_LoadBMP("bonus6.bmp");  break; }
		case 7: {bon = SDL_LoadBMP("bonus7.bmp");  break; }
		case 8: {bon = SDL_LoadBMP("bonus8.bmp"); break; }
		}
		SDL_Texture *bont = SDL_CreateTextureFromSurface(rend, bon);
		SDL_RenderCopy(rend, bont, NULL, NULL);
		SDL_DestroyTexture(bont);
		SDL_FreeSurface(bon);
	}

	void render(SDL_Renderer *renderer) {
		if ((bonus > 0) && (bonus != 3)) {
			DrawBonus(renderer);
			bonus = 0;
			SDL_RenderPresent(renderer);
			SDL_Delay(1000);
		}
		background(renderer);
		DrawCar(renderer);
		DrawBall(renderer);
		DrawCart(renderer);
		DrawScore(renderer);
		DrawLife(renderer);
		DrawLvl(renderer);
		SDL_RenderPresent(renderer);
	}

	bool Nextlvl = false;
	void update(int click) {
		CarMove(click);
		if (!lost) {
			MoveBall();
		}
		else {
			ball.CoordX = car.coordX + 20;
			ball.CoordY = car.coordY - 30;
		}
		if (win)
		{
			if (lvl == 5) {
				Win();
				quit = true;
			}
			else lvl++;
			Nextlvl=true;

		}
	}

	void NextLvl() {
		Car car{ 389,578,0,60 };
		Ball ball{ 421,543,0,lvl * 5 + 5,1,-1 };
		lost = true;
		quit = false;
		win = false;
		Game(true);
	}

	bool GetExit(int x, int y)
	{
		for (int i = 0; i < 4; i++)
		{
			if (x < 1000 && x>800 && y < 600 && y>540)
				return true;
		}
		return false;
	}

	void Load() {
		FILE * fd;
		fopen_s(&fd, "save.txt", "r");
		fseek(fd, 0, SEEK_END);
		long pos = ftell(fd);
		fseek(fd, 0, SEEK_SET);
		if (pos > 0)
		{
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					fscanf_s(fd, "%d", &Cart[i][j]);
				}
			}//LoadCart();
			fscanf(fd, "%d%d", &ball.vx, &ball.vy);
			//LoadBalls();
			fscanf(fd, "%d", &score);
			//LoadSchet();
			fscanf(fd, "%d", &Life);
			//LoadLife();
			fclose(fd);
		}
		else { fclose(fd); }

	}

	int GetSave(int x, int y) {
		if ((y > 128) && (y < 162)) {
			if ((x > 44) && (x < 113)) return 1;
			else if ((x > 132)&(x < 201)) return 2;
			else if ((x > 231) && (x < 337)) return 3;
			else return -1;
		}
		else return -1;
	}

	void NeedSave() {
		SDL_Event event;
		SDL_Window* ex = SDL_CreateWindow("Do you whant save it?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 200, SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(ex, -1, 0);
		SDL_Surface* exe = SDL_LoadBMP("exit.bmp");
		SDL_Texture *exet = SDL_CreateTextureFromSurface(renderer, exe);
		SDL_RenderCopy(renderer, exet, NULL, NULL);
		SDL_RenderPresent(renderer);
		int q = -1;

		do {


			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					q = GetSave(event.button.x, event.button.y);
					if (q == 1) {
						Save(); q = 3;
					}
					else if (event.type == SDL_QUIT) q = 3;
				}
			}


		} while (q == -1);

		if (q == 3) quit = true;
		SDL_DestroyTexture(exet);
		SDL_FreeSurface(exe);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(ex);


	}
	int Save() {
		FILE * fd;
		fopen_s(&fd, "save.txt", "r+");
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				fprintf(fd, "%d ", Cart[i][j]);
			}
			fprintf(fd, "\n");
		}//SaveCart();
		fprintf(fd, "%d %d ", ball.vx, ball.vy);
		//SaveBalls();
		fprintf(fd, "%d ", score);
		InRecords(score);
		//SaveSchet();
		fprintf(fd, "%d", Life);
		//SaveLife();
		fclose(fd);
		return 0;
	}

	int MLoad() {
		lost = true;
		quit = false;
		win = false;
		Game(false);
		return -1;
	}
	void Game(bool New) {

		SDL_Event event;
		SDL_Window* window = SDL_CreateWindow("Arcanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
		int click = 0;


		InitGame(renderer);
		if (!New) { Load(); }
		else
		{
			ReadCart();
		}

		while (!quit)
		{


			if (SDL_PollEvent(&event))
			{
				if (event.key.keysym.sym == SDLK_SPACE) {
					lost = false;
				}
				if (event.key.keysym.sym == SDLK_LEFT) { click = -1; }
				else if (event.key.keysym.sym == SDLK_RIGHT) { click = 1; }
				else click = 0;
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					quit = GetExit(event.button.x, event.button.y);
					if (quit) { NeedSave(); }
				}
				else if (event.type == SDL_QUIT) quit = true;
			}
			update(click);
			click = 0;
			render(renderer);
		}
		FreeGame();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		if (Nextlvl)NextLvl();

	}

	int NewGame() {
		Car car{ 15,578,0,150 };
		Ball ball{ 15,563,4,12,-1,-1 };
		lost = true;
		quit = false;
		win = false;
		lvl = 1;
		score = 0;
		Life = 3;
		Game(true);
		return -1;
	}
