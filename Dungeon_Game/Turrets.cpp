#include "Turrets.h"



// Laser turrets
void Laser::Render(SDL_Renderer* renderer, SDL_Texture* LaserImg)
{
    SDL_RenderCopyEx(renderer, LaserImg, NULL, &this->ShotHitbox, this->angle*(180.0 / M_PI) +90, NULL,SDL_FLIP_NONE);
}

void Turret_Laser::Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player)
{
    int RenderFrame = 42; // 24 frames

    // Get player location
    int player_x = camera.x + SCREEN_WIDTH / 2;
    int player_y = camera.y + SCREEN_HEIGHT / 2;


    if (!this->shot.OnCooldown && !this->shot.shooting)
    {
        this->shot.shooting = true;
        this->shot.updatedshot = false;
        this->shot.OnCooldown = true;
    }

    // Calculate the angle and starting position on the camera
    if (!this->shot.updatedshot && this->shot.shooting)
    {
        this->shot.ShotHitbox.w = TILE_SIZE;
        this->shot.ShotHitbox.h = TILE_SIZE;
        this->shot.ShotHitbox.x = this->x *TILE_SIZE - camera.x;
        this->shot.ShotHitbox.y = this->y *TILE_SIZE - camera.y;

        // Corrected Angle Calculation
        this->shot.angle = atan2((float)SCREEN_HEIGHT / 2 - this->shot.ShotHitbox.y, (float)SCREEN_WIDTH / 2 - this->shot.ShotHitbox.x);

        //  Corrected Velocity Assignment
        this->shot.x_speed = this->shot.speed * cos(this->shot.angle) * delta;
        this->shot.y_speed = this->shot.speed * sin(this->shot.angle) * delta;
        // Starting pos 
        this->shot.x = this->x * TILE_SIZE;
        this->shot.y = this->y * TILE_SIZE;

        this->shot.updatedshot = true;
    }

    // Check cooldown
    Uint32 CurrentT = SDL_GetTicks();
    if (this->shot.OnCooldown && CurrentT > this->shot.lastTimeShot + this->shot.cooldown)
    {
        this->shot.OnCooldown = false;
        this->shot.lastTimeShot = CurrentT;
    }

    this->shot.ShotHitbox.x = this->shot.x - camera.x + TILE_SIZE / 2;
    this->shot.ShotHitbox.y = this->shot.y - camera.y + TILE_SIZE / 2;

    // Update bullet position
    if (this->shot.shooting && CurrentT > this->shot.lastTimeRender + RenderFrame && !Bullet_Hit(camera, ColliderMap, player))
    {
        this->shot.x += this->shot.x_speed;
        this->shot.y += this->shot.y_speed;
        this->shot.lastTimeRender = CurrentT;
    }

    if(this->shot.shooting)
        this->shot.Render(renderer, laserImg);
}
bool Turret_Laser::Bullet_Hit(SDL_Rect camera, vector<vector<int>>& ColliderMap, Player& player)
{
    // Out of screen check
    if (this->shot.ShotHitbox.x> SCREEN_WIDTH || this->shot.ShotHitbox.y > SCREEN_HEIGHT || this->shot.ShotHitbox.x < 0 || this->shot.ShotHitbox.y < 0)
    {
        this->shot.shooting = false;
        return true;
    }

    int a = this->shot.x / TILE_SIZE;
    int b = this->shot.y / TILE_SIZE;

    int tile_n = ColliderMap[b][a];

    // Collision check
    if (tile_n == 1)  // Walls
    {
        this->shot.shooting = false;
        return true;
    }
    else if (Check_Surrounding_Laser(box, a, b, ColliderMap))
    {
        this->shot.shooting = false;
        return true;
    }
    else if (CheckCollisionRect(player.player_box, this->shot.ShotHitbox))  // No collision
    {
        player.hp -= 1;
        this->shot.shooting = false;
        cerr << "Hp: " << player.hp << endl;
        if (player.hp == 0)
        {
            player.alive = false;
        }
        return true;
    }
    return false;
}

bool Turret_Laser::Check_Surrounding_Laser(int n_decal, int a, int b, vector<vector<int>>& ColliderMap)
{
    SDL_Rect TempTile = { 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_Rect shot_hitbox = { shot.x - TILE_SIZE / 2, shot.y - TILE_SIZE / 2, TILE_SIZE, TILE_SIZE };

    int mapHeight = ColliderMap.size();
    int mapWidth = ColliderMap[0].size();

    for (int i = -1; i <= 1; i++)
    {
        for (int k = -1; k <= 1; k++)
        {
            int checkX = a + k;
            int checkY = b + i;

            // Prevent out-of-bounds access
            if (checkX < 0 || checkY < 0 || checkX >= mapWidth || checkY >= mapHeight)
                continue;

            if (ColliderMap[checkY][checkX] == n_decal)
            {
                TempTile.x = checkX * TILE_SIZE;
                TempTile.y = checkY * TILE_SIZE;

                if (CheckCollisionRect(shot_hitbox, TempTile))
                {
                    ColliderMap[checkY][checkX] = 0;
                    return true;
                }
            }
        }
    }
    return false;
}
