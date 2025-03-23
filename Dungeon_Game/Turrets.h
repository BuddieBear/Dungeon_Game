#pragma once

#include "Basis.h"
#include "SDL_Utils.h"

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
};



void Store_Turret_Wall_Location(vector<Turret_Wall>& Wall_Turrets, vector<vector<int>> ColliderMap);
void Turret_Connect(SDL_Rect camera, vector<vector<int>>& ColliderMap);

void Store_Turret_Laser_Location(vector<Turret_Laser>& Laser_Turrets, vector<vector<int>>& ColliderMap);
void All_Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<Turret_Laser>& Laser_Turrets, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, SDL_Rect player_box, bool& player_alive, int& player_hp);
void Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, Turret_Laser& Turret, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, SDL_Rect player_box, bool& player_alive, int& player_hp);
bool Bullet_Hit(Turret_Laser& Turret, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Rect player_box, bool& player_alive, int& player_hp);
bool Check_Surrounding_Laser(Laser shot, int n_decal, int a, int b, vector<vector<int>>& ColliderMap);
