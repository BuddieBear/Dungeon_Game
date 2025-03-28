
#include "MainMenu.h"
 // Include the header for stage 1

Menu::Menu(SDL_Renderer* render, TTF_Font* font)
    : renderer(render), font(font), selectedIndex(-1) 
{
    menuItems = { "Play", "Options", "Exit" };
}

Menu::~Menu() {}

SDL_Texture* Menu::RenderText(const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Menu::RenderMenu() {
    SDL_Color normalColor = { 255, 255, 255 }; // White
    SDL_Color highlightColor = { 255, 0, 0 }; // Red

    int menuWidth = 200;
    int menuHeight = 50;
    int spacing = 20;
    int startY = (600 - (menuItems.size() * (menuHeight + spacing))) / 2;

    for (size_t i = 0; i < menuItems.size(); ++i) {
        SDL_Color color = (i == selectedIndex) ? highlightColor : normalColor;
        SDL_Texture* textTexture = RenderText(menuItems[i], color);

        if (textTexture) {
            SDL_Rect textRect = { 300, startY + i * (menuHeight + spacing), menuWidth, menuHeight };
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
    }
}

bool Menu::ShowMenu(SDL_Renderer* renderer) {
    SDL_Event e;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return false; // Exit the game
            }
            if (e.type == SDL_MOUSEMOTION) {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                int menuWidth = 200;
                int menuHeight = 50;
                int spacing = 20;
                int startY = (600 - (menuItems.size() * (menuHeight + spacing))) / 2;

                selectedIndex = -1;
                for (size_t i = 0; i < menuItems.size(); ++i) {
                    SDL_Rect buttonRect = { 300, startY + i * (menuHeight + spacing), menuWidth, menuHeight };
                    if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                        mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
                        selectedIndex = i;
                    }
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                if (selectedIndex == 0) 
                { // Start Game button
                    RunStage1 stage1(renderer);
                    stage1.RunGame(renderer);
                }
                else if (selectedIndex == 2) { // Exit button
                    return false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        RenderMenu();
        SDL_RenderPresent(renderer);
    }
    return true;
}