#pragma once


void InRecords(int sc);//добавление в табличку
void LoadRecords(SDL_Renderer *rend);// подгрузка из файла и отрисовка
int Score();
void DrawBack(SDL_Renderer *ren);
void DrawScore(SDL_Renderer *rend, int i, int score);