#include "MainMenu.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
    Game MainGame;
    SDL_Window* window = MainGame.getWindow();
    SDL_Renderer* renderer = MainGame.getRenderer();

    TTF_Font* font = TTF_OpenFont("UI_Elements/fonts/Arial.ttf", 30);

    Menu game(renderer, font);
    game.ShowMenu(renderer);

   
    return 0;
}
