#include "GameManager.h"

Game::Game()
{
	initSDL(window, renderer, Screen_Window);
}
Game::~Game()
{
	quitSDL(window, renderer);
}

SDL_Window* Game::getWindow()
{
	return window;
}
SDL_Renderer* Game::getRenderer()
{
	return renderer;
}