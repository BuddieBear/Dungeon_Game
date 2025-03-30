#pragma once

#include "Basis.h"
#include "Character.h"
#include "SDL_Utils.h"

std::vector<std::vector<int>> LoadCSVMap(const std::string& filename);
void GetStageArray( std::vector <std::vector<int>> &Stage, int n_map);
void LoadTileTextures(SDL_Renderer* renderer, vector<SDL_Texture*> &TileTextures);
void RenderStage(SDL_Renderer* renderer, std::vector<std::vector<int>>& tileMap, Player& player, const vector<SDL_Texture*>& TileTextures);
void RenderCollider(SDL_Renderer* renderer, std::vector<std::vector<int>>& tileMap, Player& player, const vector<SDL_Texture*>& TileTextures);

