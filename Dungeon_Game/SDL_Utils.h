#pragma once

using namespace std;
#include "Basis.h"


void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& surface);
void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture* LoadTexture(const std::string imgfile, SDL_Renderer* renderer);
bool CheckCollisionRect(const SDL_Rect& a, const SDL_Rect& b);
