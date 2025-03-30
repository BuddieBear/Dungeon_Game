#pragma once

#include "Basis.h"
#include "GameRunner.h"

class Menu 
{
private:
    int menuWidth = 200;
    int menuHeight = 60;
    int spacing = 70;
    int startY = 200;
    int startX = 120;

    SDL_Texture* background;
    SDL_Rect BackgroundBox;

    TTF_Font* font;
    int Index;
    std::vector<std::string> menuItems;

    
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();

    SDL_Texture* RenderText(SDL_Renderer * renderer, const std::string& text, SDL_Color color);
    void RenderMenu(SDL_Renderer* renderer);
    GameState ShowMenu(SDL_Renderer* renderer); // Displays menu & returns true if "Start" is selected
};