#include "Turrets.h"


// Fire Wall Turrets
void Store_Turret_Wall_Location(vector<Turret_Wall>& Wall_Turrets, vector<vector<int>> ColliderMap)
{
    int n_rows = ColliderMap.size();
    int n = ColliderMap[0].size();

    
    for (int i =0; i < n_rows; i++) 
    {
        for (int k =0; k < n; k++) 
        {
            if (ColliderMap[i][k] == wall_turret_2)
            {
                Turret_Wall newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.health = 2;
                Wall_Turrets.push_back(newTurret);
            }
            else if (ColliderMap[i][k] == wall_turret_1)
            {
                Turret_Wall newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.health = 1;
                Wall_Turrets.push_back(newTurret);
            }
        }
    }
}


void Turret_Connect(SDL_Rect camera, vector<vector<int>>& ColliderMap)
{
    int x0 = camera.x / TILE_SIZE;
    int y0 = camera.y / TILE_SIZE;
    int mapHeight = ColliderMap.size();
    int mapWidth = ColliderMap[0].size();

    for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; x++)
        {
            int gridX = x + x0;
            int gridY = y + y0;

            // Ensure within bounds
            if (gridY >= mapHeight || gridX >= mapWidth) continue;

            // If turret is found, check for connections
            if (ColliderMap[gridY][gridX] == wall_turret_1 || ColliderMap[gridY][gridX] == wall_turret_2)
            {
                int turretType = ColliderMap[gridY][gridX];  // Save turret type

                // 1) Check Down for another turret
                for (int i = gridY + 1; i < mapHeight; i++)
                {
                    if (ColliderMap[i][gridX] == turretType)  // Another turret found
                    {
                        cerr << "Connected Down!" << endl;
                        // Fill the space in between with wall_fire
                        for (int j = gridY + 1; j < i; j++)
                        {
                            ColliderMap[j][gridX] = wall_fire;
                        }
                        break;
                    }
                    if (ColliderMap[i][gridX] != 0) break; // Stop if blocked
                }

                // 2) Check Right for another turret
                for (int k = gridX + 1; k < mapWidth; k++)
                {
                    if (ColliderMap[gridY][k] == turretType)  // Another turret found
                    {
                        cerr << "Connected Right!" << endl;
                        // Fill the space in between with wall_fire
                        for (int j = gridX + 1; j < k; j++)
                        {
                            ColliderMap[gridY][j] = wall_fire;
                        }
                        break;
                    }
                    if (ColliderMap[gridY][k] != 0) break; // Stop if blocked
                }
            }
        }
    }
}

// Laser turrets

void Laser::Render(SDL_Renderer* renderer, SDL_Texture* LaserImg)
{
    SDL_RenderCopyEx(renderer, LaserImg, NULL, &this->ShotHitbox, this->angle*(180.0 / M_PI) +90, NULL,SDL_FLIP_NONE);
}
void Store_Turret_Laser_Location(vector<Turret_Laser>& Laser_Turrets, vector<vector<int>>& ColliderMap)
{
    int n_rows = ColliderMap.size();
    int n = ColliderMap[0].size();

    
    for (int i = 0; i < n_rows; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (ColliderMap[i][k] == laser_turret_2)
            {
                Turret_Laser newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.shot.cooldown = 700;
                Laser_Turrets.push_back(newTurret);

            }
            else if (ColliderMap[i][k] == laser_turret_1)
            {
                Turret_Laser newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.shot.cooldown = 2100;
                Laser_Turrets.push_back(newTurret);              
            }
        }
    }
}
void All_Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<Turret_Laser>& Laser_Turrets, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, SDL_Rect player_box, bool& player_alive, int& player_hp)
{
    for (auto& turret : Laser_Turrets)
    {
        int map_x = turret.x * TILE_SIZE;
        int map_y = turret.y * TILE_SIZE;
        if (map_x >= camera.x - 400 && map_y >= camera.y- 400 &&
            map_x <= camera.x + SCREEN_WIDTH +100 && map_y <= camera.y + SCREEN_HEIGHT + 100)
        {

            Turret_Shoot(renderer, camera, turret, ColliderMap, laserImg, delta, player_box, player_alive, player_hp);
        }
    }
}

void Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, Turret_Laser& Turret, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, SDL_Rect player_box, bool& player_alive, int& player_hp)
{
    int RenderFrame = 42; // 24 frames

    // Get player location
    int player_x = camera.x + SCREEN_WIDTH / 2;
    int player_y = camera.y + SCREEN_HEIGHT / 2;


    if (!Turret.shot.OnCooldown && !Turret.shot.shooting)
    {
        Turret.shot.shooting = true;
        Turret.shot.updatedshot = false;
        Turret.shot.OnCooldown = true;
    }

    // Calculate the angle and starting position on the camera
    if (!Turret.shot.updatedshot && Turret.shot.shooting)
    {
        Turret.shot.ShotHitbox.w = TILE_SIZE;
        Turret.shot.ShotHitbox.h = TILE_SIZE;
        Turret.shot.ShotHitbox.x = Turret.x *TILE_SIZE - camera.x;
        Turret.shot.ShotHitbox.y = Turret.y *TILE_SIZE - camera.y;

        // Corrected Angle Calculation
        Turret.shot.angle = atan2((float)SCREEN_HEIGHT / 2 - Turret.shot.ShotHitbox.y, (float)SCREEN_WIDTH / 2 - Turret.shot.ShotHitbox.x);

        //  Corrected Velocity Assignment
        Turret.shot.x_speed = Turret.shot.speed * cos(Turret.shot.angle) * delta;
        Turret.shot.y_speed = Turret.shot.speed * sin(Turret.shot.angle) * delta;
        // Starting pos 
        Turret.shot.x = Turret.x * TILE_SIZE;
        Turret.shot.y = Turret.y * TILE_SIZE;

        Turret.shot.updatedshot = true;
    }

    // Check cooldown
    Uint32 CurrentT = SDL_GetTicks();
    if (Turret.shot.OnCooldown && CurrentT > Turret.shot.lastTimeShot + Turret.shot.cooldown)
    {
        Turret.shot.OnCooldown = false;
        Turret.shot.lastTimeShot = CurrentT;
    }

    Turret.shot.ShotHitbox.x = Turret.shot.x - camera.x + TILE_SIZE / 2;
    Turret.shot.ShotHitbox.y = Turret.shot.y - camera.y + TILE_SIZE / 2;

    // Update bullet position
    if (Turret.shot.shooting && CurrentT > Turret.shot.lastTimeRender + RenderFrame && !Bullet_Hit(Turret, camera, ColliderMap, player_box, player_alive, player_hp))
    {
        Turret.shot.x += Turret.shot.x_speed;
        Turret.shot.y += Turret.shot.y_speed;
        Turret.shot.lastTimeRender = CurrentT;
    }

    if(Turret.shot.shooting)
        Turret.shot.Render(renderer, laserImg);
}
bool Bullet_Hit( Turret_Laser& Turret, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Rect player_box, bool& player_alive, int& player_hp)
{
    // Out of screen check
    if (Turret.shot.ShotHitbox.x> SCREEN_WIDTH || Turret.shot.ShotHitbox.y > SCREEN_HEIGHT || Turret.shot.ShotHitbox.x < 0 || Turret.shot.ShotHitbox.y < 0)
    {
        Turret.shot.shooting = false;
        return true;
    }

    int a = Turret.shot.x / TILE_SIZE;
    int b = Turret.shot.y / TILE_SIZE;

    int tile_n = ColliderMap[b][a];

    // Collision check
    if (tile_n == 1)  // Walls
    {
        Turret.shot.shooting = false;
        return true;
    }
    else if (Check_Surrounding_Laser(Turret.shot, box, a, b,ColliderMap))
    {
        ColliderMap[b][a] = 0;
        Turret.shot.shooting = false;
        return true;
    }
    else if (CheckCollisionRect(player_box,Turret.shot.ShotHitbox))  // No collision
    {
        player_hp -= 1;
        if (player_hp == 0)
        {
            player_alive = false;
        }
        cerr << "HP: " << player_hp << endl;
        Turret.shot.shooting = false;
        return false;
    }
}

bool Check_Surrounding_Laser(Laser shot, int n_decal, int a, int b, vector<vector<int>>& ColliderMap)
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
