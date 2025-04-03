#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
#include "Character.h"
#include "GameLayout.h"
#include "Ghost.h"
#include "TurretManager.h"
#include "GameUI.h"
#include "MinionManager.h"
#include "AudioSet.h"

enum Difficulty {Easy, Hard};

class RunStage
{
private:
    SDL_Rect camera;
    float deltaTime = 0;
    bool running = true;

    // character player
    Player player;

    //Layout1 map
    vector<SDL_Texture*> Tile_Array;
    vector<vector<int>> stage_map, stage_collider;

    TurretManager Turrets;
    SDL_Texture* Laser_Texture;

    //Ghost
    SDL_Texture* GhostImg;
    ghost KillGhost;

    //GameUI
    InGameUI UserInterface;

    //Difficulty
    Difficulty Mode;
    GameState current;

    //Minion
    MinionManager Minions;
    
public:
    RunStage(SDL_Renderer* renderer, int stage, Difficulty diff);
    GameState RunGame(SDL_Renderer* renderer, AudioSet& Audio);
    ~RunStage();
};

