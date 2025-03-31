#include "GameRunner.h"

RunStage1::RunStage1(SDL_Renderer* renderer, Difficulty diff)
{
    Mode = diff;
    // Player - class
    player.x = start_1_x;
    player.y = start_1_y;
    player.PlayerInit(LoadTexture("Characters/Cowboy/Main.png", renderer), LoadTexture("Images/Bullet.png", renderer), renderer);

    //Ghost
    GhostImg = LoadTexture("Characters/Ghost/Ghost.png", renderer);
    KillGhost.ghostInit(GhostImg, camera);

    // Load Stage Texture
    LoadTileTextures(renderer, Tile_Array);
    string MapBaseFile;
    string MapColliderFile;

    if (Mode == Hard) // Ghost, Tier 1 + Tier 2 turrets, No minions, Dense Map
    {
        MapBaseFile = "Map/Stage_1_Map_Base_Hard.csv";
        MapColliderFile = "Map/Stage_1_Map_Collider_Hard.csv";
    }
    else if (Mode == Easy) //No ghost, All tier 1 turrets, No minions, Hollow Map
    {
        MapBaseFile = "Map/Stage_1_Map_Base_Easy.csv";
        MapColliderFile = "Map/Stage_1_Map_Collider_Easy.csv";
        KillGhost.alive = false;
    }

    GetStageArray(stage_1, MapBaseFile);
    GetStageArray(stage_1_collider, MapColliderFile);
    
    // Turrets
    Turrets.Store_Turret_Wall_Location( stage_1_collider);
    Turrets.Store_Turret_Laser_Location( stage_1_collider);
    Laser_Texture = LoadTexture("Images/Laser.png", renderer);

    //GameUI
    UserInterface.Init(renderer);

    RenderStage(renderer, stage_1, player, Tile_Array);
    SDL_RenderPresent(renderer);
}

RunStage1::~RunStage1()
{
    SDL_DestroyTexture(GhostImg);
    SDL_DestroyTexture(Laser_Texture);
    for (auto tex : Tile_Array) SDL_DestroyTexture(tex);
}

GameState RunStage1::RunGame(SDL_Renderer* renderer)
{
    srand(time(0));
    Uint64 lastTime = SDL_GetTicks();

    while (running && player.alive)
    {
        Uint64 CurrentTime = SDL_GetTicks();
        deltaTime = (CurrentTime - lastTime) / 1000.0f * 1.40; // Convert to seconds
        lastTime = CurrentTime;

        //Render Stage
        RenderStage(renderer, stage_1, player, Tile_Array);
        RenderCollider(renderer, stage_1_collider, player, Tile_Array);

        SDL_Delay(6);
        //Player Related Controls
        player.bullets.Shoot_bullets(renderer, stage_1_collider, Turrets.Turret_Wall_location, Turrets.Turret_Laser_location, deltaTime, camera, false);
        player.Handle_Movement(renderer, stage_1_collider,Turrets.Turret_Wall_location, Turrets.Turret_Laser_location, deltaTime, camera);

        //Turrets
        Turrets.RunTurrets(renderer, camera, stage_1_collider, Laser_Texture, deltaTime, player);

        //Ghost
        KillGhost.RunGhost(renderer, camera, player, deltaTime);

        //Render UI elements
        UserInterface.RenderPlayerBar(renderer, player);


        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    //Add the display for win/loss
    return MainMenu;
    SDL_Delay(500);
}