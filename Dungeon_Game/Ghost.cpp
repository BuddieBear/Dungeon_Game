#include "Ghost.h"


void ghost::ghostInit(int x0, int y0, SDL_Texture* TextGhost, const SDL_Rect& camera)
{
	x = x0;
	y = y0;
	this->GhostImg = TextGhost;
	this->GhostHitbox = { this->x - camera.x - GhostSize/2 , this->y - camera.y - GhostSize / 2, this->GhostSize, this->GhostSize };
}

void ghost::RunGhost(SDL_Renderer* renderer,const SDL_Rect& camera, Player& player, const float& delta)
{
	if (this->alive == false)
	{
		return;
	}
	else if (!HitPlayer(player.player_box, camera))
	{
		Move(renderer, player.player_box, camera, delta);
		Render(renderer, camera);
	}
	else { player.alive = false; cerr << "BOO! >:)"; }
}


void ghost::Move(SDL_Renderer* renderer, const SDL_Rect& player, const SDL_Rect& camera, const float& delta)
{
	Uint32 currentTime = SDL_GetTicks(); // Get current time
	static Uint32 lastUpdateTime = 0; // Update last update time

	Uint32 Interval = 24;
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

		this->x += this->x_speed;
		this->y += this->y_speed;

		// Corrected screen-space hitbox position
		this->GhostHitbox.x = (this->x - camera.x) - GhostSize / 2;
		this->GhostHitbox.y = (this->y - camera.y) - GhostSize / 2;
	}
	return;
}

bool ghost::HitPlayer(const SDL_Rect& player, const SDL_Rect& camera)
{
	if (CheckCollisionRect(this->GhostHitbox, player))
	{
		return true;
	}
	return false;
}

void ghost:: Render(SDL_Renderer* renderer, const SDL_Rect& camera)
{
	SDL_RenderCopy(renderer, this->GhostImg, NULL, &this->GhostHitbox);
}

/*
*/