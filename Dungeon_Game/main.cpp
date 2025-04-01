
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
            RunStage1 stage_1(renderer, Easy);
            state = stage_1.RunGame(renderer);
        }
        else if (state == Stage_1_Hard)
        {
            RunStage1 stage_1(renderer, Hard);
            state = stage_1.RunGame(renderer);
        }
        else if (state == Stage_2_Easy) // Stage 2
        {

        }
        else if (state == Stage_2_Hard) 
        {

        }
    }

    return 0;
}
