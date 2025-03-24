#include "Minions.h"


void ghost::ghostInit(int x0, int y0, SDL_Texture* TextGhost, SDL_Rect camera)
{
	x_speed = 0;
	y_speed = 0;
	angle = 0;
	x = x0; y = y0;
	this->GhostImg = TextGhost;
	this->GhostHitbox = { this->x - camera.x - GhostSize/2, this->y - camera.y - GhostSize / 2, this->GhostSize, this->GhostSize };
}
void ghost::Move(SDL_Renderer* renderer, SDL_Rect player, SDL_Rect camera, float delta) // moves if (!hitplayer)
{
	//calculate the angle and speed everytime
	int x_screen = this->x - camera.x;
	int y_screen = this->y - camera.y;

	this->angle = atan2((SCREEN_HEIGHT / 2) - y_screen, (SCREEN_WIDTH / 2) - x_screen);
	this->x_speed = this->speed * cos(angle) * delta;
	this->y_speed = this->speed * sin(angle) * delta;

	//Update location
	this->x += this->x_speed;
	this->y += this->y_speed;

	this->GhostHitbox.x = this->x - camera.x - GhostSize / 2;
	this->GhostHitbox.y = this->y - camera.y - GhostSize / 2;

}

// if (hit player), delete this ghost from the vector
bool ghost::HitPlayer(SDL_Rect player, SDL_Rect camera)
{
	if (CheckCollisionRect(this->GhostHitbox, player))
	{
		this->alive = false;
		return true;
	}
	return false;
}

void ghost:: Render(SDL_Renderer* renderer, SDL_Rect camera)
{
	SDL_RenderCopy(renderer, this->GhostImg, NULL, &this->GhostHitbox);
}