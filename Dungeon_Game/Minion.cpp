#include "Minion.h"

void Melee_Minion::Init(int startX, int startY, const SDL_Rect& camera)
{
	x = startX;
	y = startY;
	this->Hitbox = { this->x - camera.x - MinionSize / 2 , this->y - camera.y - MinionSize / 2, this->MinionSize, this-> MinionSize };
}

void  Melee_Minion::Run(SDL_Renderer* renderer, const SDL_Rect& camera, Player& player, SDL_Texture* Minion_Text, vector<vector<int>>& ColliderMap, const float& delta)
{
	if (this->alive == false)
	{
		return;
	}
	else if (!HitPlayer(player, camera))
	{
		Move(renderer, player.player_box, camera, ColliderMap, delta);
		Render(renderer, Minion_Text, camera);
	}
	else { player.alive = false; cerr << "Hit >:)"; }
}


void  Melee_Minion::Move(SDL_Renderer* renderer,const SDL_Rect& player, const SDL_Rect& camera, vector <vector<int>>& ColliderMap, const float& delta)
{
	Uint32 currentTime = SDL_GetTicks(); // Get current time
	Uint32 Interval = 12;
	// Check if enough time has passed
	if (currentTime - lastUpdateTime > Interval)
	{
		lastUpdateTime = currentTime;
		int x_screen = this->x - camera.x;
		int y_screen = this->y - camera.y;

		// Calculate movement direction towards player (center of screen)
		this->angle = atan2((SCREEN_HEIGHT / 2) - y_screen, (SCREEN_WIDTH / 2) - x_screen);

		// Apply movement with delta time
		this->x_speed = this->speed * cos(angle);
		this->y_speed = this->speed * sin(angle);

		int newX = x + x_speed;
		int newY = y + y_speed;

		int tileX = newX / TILE_SIZE;
		int tileY = newY / TILE_SIZE;

		// Corrected screen-space hitbox position
		this->Hitbox.x = (this->x - camera.x) - MinionSize / 2;
		this->Hitbox.y = (this->y - camera.y) - MinionSize / 2;

		

		if (ColliderMap[tileY][tileX] == 1) 
		{
			return;
			// Wall detected, stop movement
		}
		else if (ColliderMap[tileY][tileX] == box) 
		{
			// Box detected, destroy it
			ColliderMap[tileY][tileX] = 0;
			return;
		}
		else if (ColliderMap[tileY][tileX] == wall_fire)
		{
			//Walk through fire = die
			this->alive = false;
			return;
		}
		else 
		{
			this->x = newX;
			this->y = newY;
		}

	}
	return;
}

bool Melee_Minion::HitPlayer(Player& player, const SDL_Rect& camera)
{
	if (CheckCollisionRect(this->Hitbox, player.player_box))
	{
		return true;
	}
	else if (CheckCollisionRect(this->Hitbox, player.bullets.shot_hitbox) && player.bullets.shooting)
	{
		player.bullets.shooting = false;
		this->alive = false;
	}
	return false;
}

void  Melee_Minion::Render(SDL_Renderer* renderer, SDL_Texture* Melee_Text,const SDL_Rect& camera)
{
	SDL_RenderCopy(renderer, Melee_Text, NULL, &this->Hitbox);
}
