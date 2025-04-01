#include "MainMenu.h"


Menu::Menu(SDL_Renderer* renderer)
{
    font = TTF_OpenFont("UI_Elements/fonts/ShortBaby.ttf", 30);

    menuItems = { "Play   ", "Help    ", "Exit   " };
    this->background = LoadTexture("UI_Elements/Menu/MenuBG.png", renderer);
    BackgroundBox = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SelectBG = LoadTexture("UI_Elements/Menu/SelectStage.png", renderer);
    Manual = LoadTexture("UI_Elements/Menu/Manual.png", renderer);
    Loser = LoadTexture("UI_Elements/Menu/Loser.png", renderer);
    Winner = LoadTexture("UI_Elements/Menu/Winner.png", renderer);
    this->DeathReason = { 500,200,300,100 };
}

Menu::~Menu() 
{
    SDL_DestroyTexture(this->background);
    SDL_DestroyTexture(this->SelectBG);
    SDL_DestroyTexture(this->Manual);
}

SDL_Texture* Menu::RenderText(SDL_Renderer* renderer, const std::string& text, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Main Menu
void Menu::RenderMainMenu(SDL_Renderer * renderer, int Index) 
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

GameState Menu::ShowMainMenu(SDL_Renderer* renderer) 
{
    SDL_Event e;
    bool running = true;
    int Index = -1;
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
                { // Select Stage
                    return SelectStage;
                }
                else if (Index == 1)
                {
                    return Help;
                }
                else if (Index == 2) 
                { // Exit button
                    return Exit;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        RenderMainMenu(renderer, Index);
        SDL_RenderPresent(renderer);
    }
    return Exit;
}

// Select stage
GameState Menu::ShowSelectStage(SDL_Renderer* renderer)
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
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                cerr << "x,y: " << mouseX << ", " << mouseY << endl;

                if (mouseX > 250 && mouseX < 470)
                {
                    if (mouseY > 240 && mouseY < 290) // Top Left
                    {
                        return Stage_1_Easy;
                    }
                    else if (mouseY > 415 && mouseY < 460) // Bot Left
                    {
                        return Stage_2_Easy;
                    }
                }
                else if (mouseX > 800 && mouseX < 1025)
                {
                    if (mouseY > 240 && mouseY < 290) // Top Right
                    {
                        return Stage_1_Hard;
                    }
                    else if (mouseY > 415 && mouseY < 460) // Bot Right
                    {
                        return Stage_2_Hard;
                    }
                }
                if (mouseX > 480 && mouseX < 770 && mouseY > 595 && mouseY < 650)
                {
                    return MainMenu;
                }
            }
        }
        SDL_RenderClear(renderer);
        RenderSelectStage(renderer);
        SDL_RenderPresent(renderer);
    }
    return Exit;
}

void Menu::RenderSelectStage(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, this->SelectBG, NULL, &BackgroundBox);
}


// Manual
GameState Menu::ShowHelpMenu(SDL_Renderer* renderer)
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
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                if (mouseX > 470 && mouseX < 760 && mouseY > 635 && mouseY < 680)
                {
                    return MainMenu;
                }
            }
        }
        SDL_RenderClear(renderer);
        RenderHelpMenu(renderer);
        SDL_RenderPresent(renderer);
    }
    return Exit;
}

void Menu::RenderHelpMenu(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, this->Manual, NULL, &BackgroundBox);
}
//Conclusion
GameState Menu::DisplayConclusion(SDL_Renderer* renderer, bool win, GameState currentstate)
{
    // Add Reason of death
    if (win == true)
    {
        cerr << " I DIDD ";
        SDL_RenderCopy(renderer, Winner, NULL, &BackgroundBox);
    }
    else
    {
        SDL_RenderCopy(renderer, Loser, NULL, &BackgroundBox);
    }
    SDL_RenderPresent(renderer);

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
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                cerr << mouseX << ", " << mouseY << endl;
                if (mouseX > 510 && mouseX < 740)
                {
                    if (mouseY > 390 && mouseY < 485)
                    {
                        return currentstate;
                    }
                    else if (mouseY > 540 && mouseY < 630)
                    {
                        return MainMenu;
                    }
                }
            }
        }
    }
    return Exit;
}