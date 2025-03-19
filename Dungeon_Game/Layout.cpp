#include "Layout.h"



std::vector<std::vector<int>> LoadCSVMap(const std::string& filename) 
{
    std::vector<std::vector<int>> map;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        logSDLError(cerr, "Failed to open CSV map: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) 
    {
        std::vector<int> row;
        std::stringstream ss(line); // using string as input
        std::string cell;

        while (std::getline(ss, cell, ',')) 
        {
            row.push_back(std::stoi(cell)); // map[i] = row
        }

        map.push_back(row); // insert new row
    }

    return map;
}

void GetStageArray(std::vector <std::vector<int>> &Stage, int n_map)
{
    string map_file;
    switch (n_map)
    {
        case 1: map_file = "Map/Stage_1_Map_Base_Map.csv"; break;
        case 2: map_file = "Map/Stage_1_Map_Collider.csv"; break;
        default: break;
    }
        
    Stage = LoadCSVMap(map_file);
    // Test array
    /*for (const auto& row : Stage) {
        for (int tile : row) {
            cerr << tile << " ";
        }
        cerr << endl;
    }*/
}

void LoadTileTextures(SDL_Renderer* renderer, vector<SDL_Texture*> &TileTextures) 
{
    for (int i = 0; i < TileCount; i++) 
    {  
        string tile_file = "Map/Tiles/Tile_" + std::to_string(i + 1) + ".png";
        TileTextures[i] = LoadTexture(tile_file, renderer);
        cerr << tile_file << endl;

    }
}

void RenderStage(SDL_Renderer* renderer, std::vector<std::vector<int>>& tileMap, player_hitbox player, const vector<SDL_Texture*> &TileTextures)
{
    
    SDL_Rect destRect;

    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;
    //Top-left cord
    int x0 = (player.x - SCREEN_WIDTH/2) / TILE_SIZE;
    int y0 = (player.y - SCREEN_HEIGHT/2) / TILE_SIZE;

    //Res 800x600
    for (int y = 0; y < SCREEN_HEIGHT/TILE_SIZE +1; y++)  // only need to render 25 width x 20 height
    {
        for (int x = 0; x < SCREEN_WIDTH/TILE_SIZE +1; x++) 
        {
            // Get the location for the tile on SCREEN
            destRect.x = x * TILE_SIZE;
            destRect.y = y * TILE_SIZE;

            if (SDL_RenderCopy(renderer, TileTextures[ tileMap[y+y0][x+x0]%25 ], NULL, &destRect) != 0)
            {
                logSDLError(cerr, "Cannot Render tileset: " );
            }
        }
    }
}

void RenderCollider(SDL_Renderer* renderer, std::vector<std::vector<int>>& tileMap, player_hitbox player, const vector<SDL_Texture*>& TileTextures)
{

    SDL_Rect destRect;

    destRect.w = TILE_SIZE;
    destRect.h = TILE_SIZE;
    //Top-left cord
    int x0 = (player.x - SCREEN_WIDTH / 2) / TILE_SIZE;
    int y0 = (player.y - SCREEN_HEIGHT / 2) / TILE_SIZE;

    //Res 800x600
    for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE + 1; y++)  // only need to render 25 width x 20 height
    {
        for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE + 1; x++)
        {
            if (tileMap[y + y0][x + x0] != 1 && tileMap[y + y0][x + x0] != 0)
            {
                // Get the location for the tile on SCREEN
                destRect.x = x * TILE_SIZE;
                destRect.y = y * TILE_SIZE;

                if (SDL_RenderCopy(renderer, TileTextures[tileMap[y + y0][x + x0] % 25], NULL, &destRect) != 0)
                {
                    logSDLError(cerr, "Cannot Render tileset: ");
                }
            }
        }
    }
}


