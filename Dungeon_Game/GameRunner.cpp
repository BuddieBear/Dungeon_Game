#include "GameRunner.h"

RunStage1::RunStage1()
{
    initSDL(window, renderer, Screen_Window);

    // Player - class
    player.x = start_1_x;
    player.y = start_1_y;
    player_decal = LoadTexture("Characters/Cowboy/Main.png", renderer);
    Bullet_Texture = LoadTexture("Images/Bullet.png", renderer);
    LoadAnimation(Walking_anim, renderer);
    LoadTileTextures(renderer, Tile_Array);
    player_box = { SCREEN_WIDTH / 2 - p_size / 2, SCREEN_HEIGHT / 2 - p_size / 2, p_size, p_size };
    // Load Stage
    GetStageArray(stage_1, 1);
    GetStageArray(stage_1_collider, 2);

    // Turrets
    Store_Turret_Wall_Location(Turret_Wall_location, stage_1_collider);
    Store_Turret_Laser_Location(Turret_Laser_location, stage_1_collider);
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
    SDL_DestroyTexture(player_decal);
    SDL_DestroyTexture(Bullet_Texture);
    for (auto tex : Walking_anim) SDL_DestroyTexture(tex);
    for (auto tex : Tile_Array) SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void RunStage1::RunGame()
{
    while (running && player_alive)
    {
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);

        SDL_Delay(6);
        Shoot_bullets(renderer, player_shot, player, Bullet_Texture, stage_1_collider, Turret_Wall_location, Turret_Laser_location, deltaTime, camera);
        Handle_Movement(running, renderer, player, p_speed, stage_1_collider, Walking_anim, deltaTime, camera, player_alive);
        Turret_Connect(camera, stage_1_collider);
        All_Turret_Shoot(renderer, camera, Turret_Laser_location, stage_1_collider, Laser_Texture, deltaTime, player_box, player_alive, player_hp);

        if (!KillGhost.HitPlayer(player_box, camera))
        {
            KillGhost.Move(renderer, player_box, camera, deltaTime);
            KillGhost.Render(renderer, camera);
        }
        else { player_alive = false; cerr << "BOO! >:)"; }
            
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    SDL_Delay(500);
    quitSDL(window, renderer);
}