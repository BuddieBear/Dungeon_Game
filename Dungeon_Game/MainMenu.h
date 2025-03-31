#pragma once

#include "Basis.h"
#include "GameRunner.h"

class Menu 
{
private:
    //Main menu
    int menuWidth = 200;
    int menuHeight = 60;
    int spacing = 70;
    int startY = 200;
    int startX = 120;
    SDL_Texture* background;
    SDL_Rect BackgroundBox;
    TTF_Font* font;
    std::vector<std::string> menuItems;

    // Select stage
    SDL_Texture* SelectBG;

    // Help
    SDL_Texture* Manual;
    
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();

    GameState ShowMainMenu(SDL_Renderer* renderer); // Displays Main Menu, return GameState
    GameState ShowSelectStage(SDL_Renderer* renderer);
    GameState ShowHelpMenu(SDL_Renderer* renderer);
    // Add Conclusion Menu
    
private: 
    SDL_Texture* RenderText(SDL_Renderer* renderer, const std::string& text, SDL_Color color);
    void RenderMainMenu(SDL_Renderer* renderer, int Index);
    void RenderSelectStage(SDL_Renderer* renderer);
    void RenderHelpMenu(SDL_Renderer* renderer);
};