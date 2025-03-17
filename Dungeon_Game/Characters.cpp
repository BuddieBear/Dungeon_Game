#include "Characters.h"


    // players

void Handle_Movement(bool& running, player_hitbox& player, const int &speed, vector <vector<int>>& ColliderMap)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_W]) Check_Collision(player,0,-speed,ColliderMap);
    if (keystates[SDL_SCANCODE_S]) Check_Collision(player, 0, speed, ColliderMap);
    if (keystates[SDL_SCANCODE_A]) Check_Collision(player, -speed, 0, ColliderMap);
    if (keystates[SDL_SCANCODE_D]) Check_Collision(player, speed, 0, ColliderMap);
}

void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap)
{
    int new_x = player.x + x_plus;
    int new_y = player.y + y_plus;
    
    new_x = new_x / TILE_SIZE -1;
    new_y = new_y / TILE_SIZE -1;

    int tile_num = ColliderMap[new_y][new_x];
    
    if (tile_num == 0)
    { 

    }
    else if (tile_num == gold_key)
    {
        //Remove the Gold gate and Gold key
        for (auto& row : ColliderMap)
        {
            for (auto& tile : row)
            {
                if (tile == gold_key || tile == gold_gate)
                {
                    tile = 0;
                }
            }
        }
    }
    else if (tile_num == silver_key)
    {
        for (auto& row : ColliderMap)
        {
            for (auto& tile : row)
            {
                if (tile == silver_key || tile == silver_gate)
                {
                    tile = 0;
                }
            }
        }
    }
    else { return; }

    player.x = player.x + x_plus;
    player.y = player.y + y_plus;
    return;
}
