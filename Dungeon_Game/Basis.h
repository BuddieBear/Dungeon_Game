#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <map>
//SDL 2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 32;

//Start position
const int start_1_x = 2000;
const int start_1_y = 5230;

const int start_2_x = 0;
const int start_2_y = 0;

//Objectives decals
const int TileCount = 30;

const int gold_gate = 17;
const int silver_gate = 15; 
const int gold_key = 19;
const int silver_key = 20;
const int box = 21;
const int wall_turret_1 = 22;
const int wall_turret_2 = 23;
const int wall_fire = 24;
const int laser_turret_1 = 25;
const int laser_turret_2 = 26;
const int Unopened_wood_chest = 28;
const int Opened_wood_chest = 29;

const int victory_crown = 27;
//Animation timing
const int Delay_Frame = 42; // 1000/24 = 42(ms) or 24 fps
const int bullet_frame = 16; // 60fpsw

//Player
const int p_size = 48;

enum GameState { MainMenu, SelectStage, Help, Exit, Stage_1_Easy, Stage_1_Hard, Stage_2 };