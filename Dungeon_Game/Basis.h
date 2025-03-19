#ifndef BASIS_H_
#define BASIS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
//SDL 2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
//New headers

/*#include "Characters.h"
#include "Layout.h"
#include "SDL_Utils.h"*/

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 32;

//Start position
const int start_1_x = 1800;
const int start_1_y = 5230;

const int start_2_x = 0;
const int start_2_y = 0;

//Objectives decals
const int gold_gate = 17;//decal num
const int silver_gate = 15; 
const int gold_key = 19;
const int silver_key = 20;

//Input delay
const int  Delay_Frame = 42; // 1000/24 = 42(ms) or 24 frames per sec


//Player
const int p_size = 48;

#endif