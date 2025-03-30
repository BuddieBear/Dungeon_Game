#include "MainMenu.h"


Menu::Menu(SDL_Renderer* renderer, TTF_Font* font)
    : font(font), Index(-1) 
{
    menuItems = { "Play   ", "Help    ", "Exit   " };
    this->background = LoadTexture("UI_Elements/Menu/Background.png", renderer);
    BackgroundBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

Menu::~Menu() 
{
    SDL_DestroyTexture(this->background);
}

SDL_Texture* Menu::RenderText(SDL_Renderer* renderer, const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Menu::RenderMenu(SDL_Renderer * renderer) 
{
    SDL_Color normalColor = { 255, 255, 255 }; // White
    SDL_Color highlightColor = { 255, 0, 0 }; // Red

    //Render background
    SDL_RenderCopy(renderer, background, NULL, &BackgroundBox);

    for (size_t i = 0; i < menuItems.size(); ++i) 
    {
        SDL_Color color = (i == Index) ? highlightColor : normalColor;
        SDL_Texture* textTexture = RenderText(renderer,menuItems[i], color);

        if (textTexture) 
        {
            SDL_Rect textRect = { startX , startY + i * (menuHeight + spacing), menuWidth, menuHeight };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
    }
}

GameState Menu::ShowMenu(SDL_Renderer* renderer) 
{
    SDL_Event e;
    bool running = true;

    while (running) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                return Exit; // Exit the game
            }
            if (e.type == SDL_MOUSEMOTION) 
            {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;

                Index = -1;
                for (size_t i = 0; i < menuItems.size(); ++i) 
                {
                    SDL_Rect buttonRect = { startX, startY + i * (menuHeight + spacing), menuWidth, menuHeight };
                    if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                        mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) 
                    {
                        Index = i;
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) 
            {
                if (Index == 0) 
                { // Start Game button
                    return Stage_1_Hard;
                }
                else if (Index == 2) 
                { // Exit button
                    return Exit;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        RenderMenu(renderer);
        SDL_RenderPresent(renderer);
    }
    return Exit;
}