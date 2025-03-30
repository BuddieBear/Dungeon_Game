#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* Screen_Window;
public:
	Game();
	~Game();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
};