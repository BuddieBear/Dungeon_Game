#include "Basis.h"
#include "SDL_Utils.h"
#include "Characters.h"
#include "Layout.h"
#include "Turrets.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* Screen_Window;
    initSDL(window, renderer, Screen_Window);

    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Player
    int p_speed = 250; // pixel per sec
    int n = 0;
    player_hitbox player;
    //Starting pos for player
    player.x = start_1_x;
    player.y = start_1_y;

    //Texture for player
    SDL_Texture* player_decal = LoadTexture("Characters/Cowboy/Main.png", renderer);
    SDL_Rect player_box; // Always in the middle of the screen
    player_box.x = SCREEN_WIDTH/2 - p_size/2;
    player_box.y = SCREEN_HEIGHT/2 - p_size/ 2;
    player_box.w = p_size;
    player_box.h = p_size;

    vector<SDL_Texture*> Walking_anim;
    LoadAnimation(Walking_anim, renderer);

    revolver player_shot;
    SDL_Texture* Bullet_Texture = LoadTexture("Images/Bullet.png", renderer);

    bool player_alive = true;
    //Load Texture for Stage
    vector<SDL_Texture*> Tile_Array(25);
    LoadTileTextures(renderer, Tile_Array);

    //Set up stage
    vector <vector<int>> stage_1, stage_1_collider;
    GetStageArray(stage_1, 1);
    GetStageArray(stage_1_collider, 2); // Collider Map

    //Entities
    vector<Turret_Wall> Turret_Wall_location;
    Store_Turret_Wall_Location(Turret_Wall_location, stage_1_collider);

  


    //Render stage based on player location
    RenderStage(renderer, stage_1, player, Tile_Array);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);

    
    Uint32 lastT = SDL_GetTicks();  // Stores the last frame time    
    //Start game
    bool running = true;
    while (running && player_alive)
    {
        //Setup delta time
        float deltaTime = (16/1000.0f); // 60 fps

        //The Stage
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);

        SDL_Delay(8);
        //Bullet
        Shoot_bullets(renderer, player_shot, player, Bullet_Texture, stage_1_collider,Turret_Wall_location, deltaTime, camera);

        //Character move
        Handle_Movement(running, renderer, player, p_speed, stage_1_collider, Walking_anim, deltaTime, camera, player_alive);

        // Turret
        Turret_Connect(camera, stage_1_collider);

        //Update new frame
        SDL_RenderPresent(renderer); 
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
