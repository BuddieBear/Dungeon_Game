#ifndef CHARACTERS_H_
#define CHARACTERS_H_


#include "Basis.h"
#include "SDL_Utils.h"
#include "Turrets.h"


struct player_hitbox
{
    int x, y;
    player_hitbox(int x0 = 0, int y0 = 0)
    {
        x = x0;
        y = y0;
    }
};

struct revolver
{
    int x_dest =0, y_dest =0; // Destination Rendered on Screen
    int x =0, y =0; // Map location

    double angle =0; // Angle between ( (Width/2 , Height/2) -> (x, y)  ) to  Ox (clockwise)
    double speed = 2000;
    double x_speed =0, y_speed =0;

    int Cooldown = 500;
    int ReloadTime = 1500;

    const int MaxAmmo = 7;
    int ammo = 7;

    void render(SDL_Renderer* renderer, SDL_Rect Dest, SDL_Texture* Bullet_Texture, bool shooting);
};



//Bullets
void Shoot_bullets(SDL_Renderer* renderer, revolver& shot, player_hitbox player, SDL_Texture* Bullet_Texture, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, float delta, SDL_Rect camera);
bool Check_BulletHit(bool& shooting, SDL_Rect shot_hitbox, revolver& shot, player_hitbox player, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets);
bool Check_Surrounding_Bullet(revolver shot, int n_decal, int a, int b, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets);

//Main Characters
void LoadAnimation(vector<SDL_Texture*>& Animation_pack, SDL_Renderer* renderer);
void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int& speed, vector <vector<int>>& ColliderMap, vector <SDL_Texture*> Animation, float delta, SDL_Rect& camera, bool& player_alive);
void RenderCharacter(vector < SDL_Texture*> Animation, SDL_Renderer* renderer, int CurrentFrame, bool FaceRight);
void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap, SDL_Rect& camera, bool& player_alive);
#endif // CHARACTERS_H_