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
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    float deltaTime = (16 / 1000.0f); // 60 fps
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
    void RunGame(SDL_Renderer* renderer);
    ~RunStage1();
};
