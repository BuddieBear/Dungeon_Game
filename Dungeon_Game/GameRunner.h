#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
#include "Character.h"
#include "GameLayout.h"
#include "Turrets.h"
#include "Ghost.h"
#include "TurretManager.h"
#include "GameUI.h"


class RunStage1 
{
private:
    SDL_Rect camera = { start_1_x - SCREEN_WIDTH/2, start_1_y -SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT };
    float deltaTime = 0;
    bool running = true;
    // character player
    Player player;

    //Layout1 map
    vector<SDL_Texture*> Tile_Array;
    vector<vector<int>> stage_1, stage_1_collider;

    TurretManager Turrets;
    SDL_Texture* Laser_Texture;

    //Ghost
    SDL_Texture* GhostImg;
    ghost KillGhost;

    //GameUI
    InGameUI UserInterface;
public:
    RunStage1(SDL_Renderer* renderer);
    GameState RunGame(SDL_Renderer* renderer);
    ~RunStage1();
};
