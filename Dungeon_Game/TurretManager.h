#pragma once
#include "Basis.h"
#include "Turrets.h"

class TurretManager
{
public:
	vector<Turret_Wall> Turret_Wall_location;
	vector<Turret_Laser> Turret_Laser_location;

public:
	void RunTurrets(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player);

	void Store_Turret_Wall_Location(vector<vector<int>> ColliderMap);
	void Turret_Connect(SDL_Rect camera, vector<vector<int>>& ColliderMap);

	void Store_Turret_Laser_Location(vector<vector<int>>& ColliderMap);
	void All_Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player);
};