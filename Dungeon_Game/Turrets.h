#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
#include "Character.h"

class Player;

struct Turret_Wall // Creates a wall of flame
{
	int x =0, y =0;  // CSV location
	int health =1;
};
struct Laser
{
	int x, y; // Map location
	double x_speed, y_speed;
	double speed = 1500;

	double angle;

	int cooldown = 2100;
    bool updatedshot = true;
    bool shooting = false;
    bool OnCooldown = false;

    SDL_Rect ShotHitbox;

    Uint32 lastTimeShot = 0;
	Uint32 lastTimeRender = 0;

	void Render(SDL_Renderer* renderer, SDL_Texture* LaserImg);
};

struct Turret_Laser
{
	int x, y; // CSV location 
	Laser shot;

	void Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player);
	bool Bullet_Hit(SDL_Rect camera, vector<vector<int>>& ColliderMap, Player& player);
	bool Check_Surrounding_Laser(int n_decal, int a, int b, vector<vector<int>>& ColliderMap);

};





