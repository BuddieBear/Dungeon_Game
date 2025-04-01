
#include "MainMenu.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
    Game MainGame;
    SDL_Window* window = MainGame.getWindow();
    SDL_Renderer* renderer = MainGame.getRenderer();

    GameState state = MainMenu;

    while (state != Exit)
    {
        if (state == MainMenu) // Main Menu
        {
            Menu game(renderer);
            state = game.ShowMainMenu(renderer);
        }
        else if (state == SelectStage)
        {
            Menu game(renderer);
            state = game.ShowSelectStage(renderer);
        }
        else if (state == Help)
        {
            Menu game(renderer);
            state = game.ShowHelpMenu(renderer);
        }
        else if (state == Stage_1_Easy) // Stage 1 
        {
            RunStage stage_1(renderer, 1, Easy);
            state = stage_1.RunGame(renderer);
        }
        else if (state == Stage_1_Hard)
        {
            RunStage stage_1(renderer, 1, Hard);
            state = stage_1.RunGame(renderer);
        }
        else if (state == Stage_2_Easy) // Stage 2
        {
            RunStage stage_2(renderer, 2, Easy);
            state = stage_2.RunGame(renderer);
        }
        else if (state == Stage_2_Hard) 
        {
            RunStage stage_2(renderer, 2, Hard);
            state = stage_2.RunGame(renderer);
        }
    }

    return 0;
}
