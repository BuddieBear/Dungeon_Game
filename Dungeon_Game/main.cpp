#include "Basis.h"
#include "SDL_Utils.h"
#include "Characters.h"
#include "Layout.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* Screen_Window;
    initSDL(window, renderer, Screen_Window);

    //Player
    int p_speed = 3;
    int n = 0;
    int p_size = 32;
    player_hitbox player;

    //Texture for player
    SDL_Texture* player_decal = LoadTexture("images/PlayerImage.png", renderer);
    SDL_Rect player_box; // Always in the middlle of the screen
    player_box.x = SCREEN_WIDTH/2 - p_size;
    player_box.y = SCREEN_HEIGHT/2 - p_size;
    player_box.w = p_size;
    player_box.h = p_size;

    //Load Texture for Stage
    vector<SDL_Texture*> Tile_Array(25);
    LoadTileTextures(renderer, Tile_Array);
    //Set up stage
    vector <vector<int>> stage_1, stage_1_collider;
    GetStageArray(stage_1, 1);
    GetStageArray(stage_1_collider, 2); // Collider Map
    
    //Starting pos for player
    player.x = start_1_x;
    player.y = start_1_y;
    //Render stage based on player location
    RenderStage(renderer, stage_1, player, Tile_Array);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    //Rendering start
    bool running = true;
    while (running)
    {
        //Start over
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Character move
        Handle_Movement(running, player, p_speed, stage_1_collider);

        //The Stage
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);
        //Render Objects on screen

        //Render players
        SDL_RenderCopy(renderer, player_decal, NULL, &player_box);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    
    //end program
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
// functions
