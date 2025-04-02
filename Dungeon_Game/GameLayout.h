#pragma once

#include "Basis.h"
#include "Character.h"
#include "SDL_Utils.h"

vector<vector<int>> LoadCSVMap(const string& filename);
void GetStageArray( std::vector <std::vector<int>> &Stage,const string& MapFile);
void LoadTileTextures(SDL_Renderer* renderer, vector<SDL_Texture*> &TileTextures);
void RenderStage(SDL_Renderer* renderer,const std::vector<std::vector<int>>& tileMap, const Player& player, const vector<SDL_Texture*>& TileTextures);
void RenderCollider(SDL_Renderer* renderer, const std::vector<std::vector<int>>& tileMap, const Player& player, const vector<SDL_Texture*>& TileTextures);

