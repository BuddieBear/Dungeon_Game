#include "GameRunner.h"

RunStage1::RunStage1()
{
    initSDL(window, renderer, Screen_Window);

    // Player - class
    player.x = start_1_x;
    player.y = start_1_y;
    player.PlayerInit(LoadTexture("Characters/Cowboy/Main.png", renderer), LoadTexture("Images/Bullet.png", renderer), renderer);

    // Load Stage
    LoadTileTextures(renderer, Tile_Array);
    GetStageArray(stage_1, 1);
    GetStageArray(stage_1_collider, 2);

    // Turrets
    Turrets.Store_Turret_Wall_Location( stage_1_collider);
    Turrets.Store_Turret_Laser_Location( stage_1_collider);
    Laser_Texture = LoadTexture("Images/Laser.png", renderer);

    //Ghost
    GhostImg = LoadTexture("Characters/Ghost/Ghost.png", renderer);
    KillGhost.ghostInit(start_1_x + 400, start_1_y + 600, GhostImg, camera);
    RenderStage(renderer, stage_1, player, Tile_Array);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
}

RunStage1::~RunStage1()
{
    SDL_DestroyTexture(GhostImg);
    SDL_DestroyTexture(Laser_Texture);
    for (auto tex : Tile_Array) SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void RunStage1::RunGame()
{
    srand(time(0));
    while (running && player.alive)
    {
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);

        SDL_Delay(6);

        //Player Related Controls
        player.bullets.Shoot_bullets(renderer, stage_1_collider, Turrets.Turret_Wall_location, Turrets.Turret_Laser_location, deltaTime, camera);
        player.Handle_Movement( renderer, stage_1_collider,deltaTime, camera);

        //Turrets
        Turrets.RunTurrets( renderer, camera, stage_1_collider, Laser_Texture, deltaTime, player);

        //Ghost
        KillGhost.RunGhost(renderer, camera, player, deltaTime);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    SDL_Delay(500);
    quitSDL(window, renderer);
}