#pragma once

#include "Basis.h"
#include "SDL_Utils.h"
#include "Turrets.h"

struct Turret_Laser;
struct Turret_Wall;
class Player;

class revolver
{
private:
    int x_dest =0, y_dest =0; // Destination on Screen
    int x =0, y =0; // Map location

    double angle =0; // Angle between ( (Width/2 , Height/2) -> (x, y)  ) to  Ox (clockwise)
    double speed = 2500;
    double x_speed =0, y_speed =0;

    int Cooldown = 500;
    int ReloadTime = 1500;  
    
    int MaxAmmo = 6;


    bool shooting = false;
    bool OnCooldown =  false;
    bool EmptyMag = false;
    bool Updated_shot = true;

    SDL_Rect shot_hitbox; // On screen only
    SDL_Texture* Img;

    Uint32 LastTimeRender = 0;
    Uint32 LastTimeShot = 0;
    
public:
    int ammo = 6;
    friend class Player;
    void get_revolver(SDL_Texture* bulletimg);
    void render(SDL_Renderer* renderer, SDL_Rect Dest);
    void Shoot_bullets(SDL_Renderer* renderer,  vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, float delta, SDL_Rect camera, bool JustShot );
    bool Check_BulletHit(vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets);
    bool Check_Surrounding_Bullet(int n_decal, int a, int b, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets);
    ~revolver();
};

class Player
{
public:
    int x, y; // Map location 
    int speed = 300;
    int hp = 10;
    int MaxHp = 10;
    bool alive = true;
    bool win = false;
    SDL_Rect player_box; // To render on screen
    revolver bullets;

private:
    SDL_Texture* Img;
    vector<SDL_Texture*> Walk_Animation;

public:
    void PlayerInit(SDL_Texture* playerText, SDL_Texture* BulletText, SDL_Renderer* renderer);
    void LoadAnimation(SDL_Renderer* renderer);
    
    void Handle_Movement(SDL_Renderer* renderer, vector <vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, float delta, SDL_Rect& camera);
    void RenderCharacter(SDL_Renderer* renderer, int CurrentFrame, bool FaceRight);
    void Check_Collision(int x_plus, int y_plus, vector <vector<int>>& ColliderMap, SDL_Rect& camera);
    bool Check_Surrounding_Player(SDL_Rect NewHitbox, int new_x, int new_y, vector<vector<int>>& ColliderMap);

    ~Player();
};
