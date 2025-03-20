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

struct bullet
{
    int x_dest, y_dest; // Destination Rendered on Screen
    int x, y; // Location on the World map
    double angle; // Angle between ( (x, y)-> (Width/2 , Height/2) ) to  | (clockwise)
    double speed = 2000;
    double x_speed, y_speed;

    int Cooldown = 500;
    int ReloadTime = 1500;

    const int MaxAmmo = 7;
    int ammo = 7;

    void render(SDL_Renderer* renderer, SDL_Rect Dest, SDL_Texture* Bullet_Texture, bool shooting);
};

bool CheckCollisionRect(const SDL_Rect& a, const SDL_Rect& b);

//Bullets
void Shoot_bullets(SDL_Renderer* renderer, bullet& shot, player_hitbox player, SDL_Texture* Bullet_Texture, vector<vector<int>>& ColliderMap, float delta, SDL_Rect camera);
bool Check_BulletHit(bool& shooting, SDL_Rect shot_hitbox, bullet& shot, player_hitbox player, vector<vector<int>> & ColliderMap);
bool Check_Surrounding_Bullet(bullet shot, int n_decal, int a, int b, vector<vector<int>>& ColliderMap);

//Main Characters
void LoadAnimation(vector<SDL_Texture*>& Animation_pack, SDL_Renderer* renderer);
void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int& speed, vector <vector<int>>& ColliderMap, vector <SDL_Texture*> Animation, float delta, SDL_Rect& camera);
void RenderCharacter(vector < SDL_Texture*> Animation, SDL_Renderer* renderer, int CurrentFrame, bool FaceRight);
void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap, SDL_Rect& camera);
#endif 
