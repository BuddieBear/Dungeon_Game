#pragma once

#include "Basis.h"
#include "GameRunner.h"
class Menu 
{
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    int selectedIndex;
    std::vector<std::string> menuItems;

    
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();

    bool ShowMenu(SDL_Renderer* renderer); // Displays menu & returns true if "Start" is selected
    SDL_Texture* RenderText(const std::string& text, SDL_Color color);
    void RenderMenu();
};