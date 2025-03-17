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
void Handle_Movement(bool& running, player_hitbox& player, const int& speed, vector <vector<int>>& ColliderMap);
void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap);
#endif 
