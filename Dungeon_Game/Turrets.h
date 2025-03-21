#pragma once

#ifndef TURRETS_H_
#define TURRETS_H_

#include "Basis.h"
#include "SDL_Utils.h"

struct Turret_Wall // Creates a wall of flame
{
	int x =0, y =0;  // CSV location
	int health =1;
};

void Store_Turret_Wall_Location(vector<Turret_Wall>& Wall_Turrets, vector<vector<int>> ColliderMap);
void Turret_Connect(SDL_Rect camera, vector<vector<int>>& ColliderMap);

#endif