
#include "MainMenu.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
    Game MainGame;
    SDL_Window* window = MainGame.getWindow();
    SDL_Renderer* renderer = MainGame.getRenderer();

    TTF_Font* Menufont = TTF_OpenFont("UI_Elements/fonts/ShortBaby.ttf", 30);

    bool GameRunning = true;

    GameState state = MainMenu;

    while (state != Exit)
    {
        if (state == MainMenu)
        {
            Menu game(renderer, Menufont);
            state = game.ShowMenu(renderer);
        }
        else if (state == Stage_1_Hard)
        {
            RunStage1 stage_1(renderer);
            state = stage_1.RunGame(renderer);
        }
    }

    return 0;
}
