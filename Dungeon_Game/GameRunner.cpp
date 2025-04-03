#include "GameRunner.h"
#include "MainMenu.h"

RunStage::RunStage(SDL_Renderer* renderer, int stage, Difficulty diff)
{
    string MapBaseFile;
    string MapColliderFile;

    
    Mode = diff;

    // Set up
    if (stage == 1)
    {
        camera = { start_1_x - SCREEN_WIDTH / 2, start_1_y - SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT };
        player.x = start_1_x;
        player.y = start_1_y;
        if (Mode == Hard) // Ghost, Tier 1 + Tier 2 turrets, No minions, Dense Map
        {
            current = Stage_1_Hard;
            MapBaseFile = "Map/Stage_1_Map_Base_Hard.csv";
            MapColliderFile = "Map/Stage_1_Map_Collider_Hard.csv";
        }
        else if (Mode == Easy) //No ghost, All tier 1 turrets, No minions, Hollow Map
        {
            current = Stage_1_Easy;
            MapBaseFile = "Map/Stage_1_Map_Base_Easy.csv";
            MapColliderFile = "Map/Stage_1_Map_Collider_Easy.csv";
            KillGhost.alive = false;
        }
    }
    else if (stage == 2)
    {
        camera = { start_2_x - SCREEN_WIDTH / 2, start_2_y - SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT };
        player.MaxHp = 50;
        player.hp = 50;

        player.x = start_2_x;
        player.y = start_2_y;
        if (Mode == Hard) // Ghost, Tier 1 + Tier 2 turrets, No minions, Dense Map
        {
            current = Stage_2_Hard;
            MapBaseFile = "Map/Stage_2_Map_Base_Hard.csv";
            MapColliderFile = "Map/Stage_2_Map_Collider_Hard.csv";
        }
        else if (Mode == Easy) //No ghost, All tier 1 turrets, No minions, Hollow Map
        {
            current = Stage_2_Easy;
            MapBaseFile = "Map/Stage_2_Map_Base_Easy.csv";
            MapColliderFile = "Map/Stage_2_Map_Collider_Easy.csv";
            KillGhost.alive = false;
        }
    }

    player.PlayerInit(LoadTexture("Characters/Cowboy/Main.png", renderer), LoadTexture("Images/Bullet.png", renderer), renderer);

    //Ghost
    GhostImg = LoadTexture("Characters/Ghost/Ghost.png", renderer);
    KillGhost.ghostInit(player.x + 600, player.y + 400, GhostImg, camera);

    // Load Stage Texture
    LoadTileTextures(renderer, Tile_Array);
  
    GetStageArray(stage_map, MapBaseFile);
    GetStageArray(stage_collider, MapColliderFile);
    
    // Turrets
    Turrets.Store_Turret_Wall_Location( stage_collider );
    Turrets.Store_Turret_Laser_Location( stage_collider );
    Laser_Texture = LoadTexture("Images/Laser.png", renderer);

    //Minion
    Minions.GetMelee_Minion(stage_collider, LoadTexture("Characters/Minions/Melee/Melee_Minion.png", renderer), camera);

    //GameUI
    UserInterface.Init(renderer);

    RenderStage(renderer, stage_map, player, Tile_Array);
    SDL_RenderPresent(renderer);
}

RunStage::~RunStage()
{
    SDL_DestroyTexture(GhostImg);
    SDL_DestroyTexture(Laser_Texture);
    for (auto tex : Tile_Array) SDL_DestroyTexture(tex);
}

GameState RunStage::RunGame(SDL_Renderer* renderer, AudioSet& Audio)
{
    Audio.PlayAmbience();

    srand(time(0));
    Uint64 lastTime = SDL_GetTicks();

    while (running && player.alive)
    {
        SDL_RenderClear(renderer);

        Uint64 CurrentTime = SDL_GetTicks();
        deltaTime = (CurrentTime - lastTime) / 1000.0f * 1.40; // Convert to seconds
        lastTime = CurrentTime;

        //Render Stage
        RenderStage(renderer, stage_map, player, Tile_Array);
        RenderCollider(renderer, stage_collider, player, Tile_Array);

        SDL_Delay(6);

        //Player Related Controls
        player.bullets.Shoot_bullets(renderer, stage_collider, Turrets.Turret_Wall_location, Turrets.Turret_Laser_location, deltaTime, camera, Audio, false);
        player.Handle_Movement(renderer, stage_collider,Turrets.Turret_Wall_location, Turrets.Turret_Laser_location, deltaTime, camera, Audio);

        //Turrets
        Turrets.RunTurrets(renderer, camera, stage_collider, Laser_Texture, deltaTime, player);

        //Minions
        Minions.Run_Melee_Minion(renderer, camera, player, stage_collider, deltaTime);

        //Ghost
        KillGhost.RunGhost(renderer, camera, player, deltaTime);

        

        //Render UI elements
        UserInterface.RenderPlayerBar(renderer, player);


        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
    }

    // Win loss display
    Mix_HaltMusic();
    Menu Conclusion(renderer);
    return Conclusion.DisplayConclusion(renderer, player.win, current, Audio);
    
}