#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#include "Basis.h"
#include "SDL_Utils.h"

struct player_hitbox
{
    int x, y;

    player_hitbox(int x0 = 0, int y0 = 0)
    {
        x = x0;
        y = y0;
    }
};
void LoadAnimation(vector<SDL_Texture*>& Animation_pack, SDL_Renderer* renderer);
void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int& speed, vector <vector<int>>& ColliderMap, vector <SDL_Texture*> Animation);
void RenderCharacter(vector < SDL_Texture*> Animation, SDL_Renderer* renderer, int CurrentFrame);
void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap);
#endif 
