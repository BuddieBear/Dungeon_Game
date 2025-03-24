#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
#include "Character.h"
#include "Layout.h"
#include "Turrets.h"
#include "Minions.h"


class RunStage1 
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* Screen_Window;
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    // character player
    int p_speed = 300;
    int player_hp = 10;
    bool player_alive = true;
    bool running = true;
    float deltaTime = (16 / 1000.0f); // 60 fps
    player_hitbox player;
    revolver player_shot;
    SDL_Texture* player_decal;
    SDL_Rect player_box;
    SDL_Texture* Bullet_Texture;
    vector<SDL_Texture*> Walking_anim;

    //Layout1 map
    vector<SDL_Texture*> Tile_Array;
    vector<vector<int>> stage_1, stage_1_collider;
    vector<Turret_Wall> Turret_Wall_location;
    vector<Turret_Laser> Turret_Laser_location;
    SDL_Texture* Laser_Texture;

    //Ghost
    SDL_Texture* GhostImg;
    ghost KillGhost;
public:
    RunStage1();
    void RunGame();
    ~RunStage1();
};
