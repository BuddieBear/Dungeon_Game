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
    player_hitbox player;

    //Texture for player
    SDL_Texture* player_decal = LoadTexture("Characters/Cowboy/Main.png", renderer);
    SDL_Rect player_box; // Always in the middlle of the screen
    player_box.x = SCREEN_WIDTH/2 - p_size;
    player_box.y = SCREEN_HEIGHT/2 - p_size;
    player_box.w = p_size;
    player_box.h = p_size;

    vector<SDL_Texture*> Walking_anim;
    LoadAnimation(Walking_anim, renderer);

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
    SDL_Delay(500);

    //Start game
    bool running = true;
    while (running)
    {
        //The Stage
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);

        //Character move
        Handle_Movement(running, renderer, player, p_speed, stage_1_collider, Walking_anim);

        //Update new frame
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        //Clear renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    
    //end program
    SDL_Delay(500);
    quitSDL(window, renderer);
    return 0;
}
// functions
