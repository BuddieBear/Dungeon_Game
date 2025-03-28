#include "TurretManager.h"

void TurretManager::RunTurrets(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player)
{
    this->Turret_Connect(camera, ColliderMap);
    this->All_Turret_Shoot(renderer, camera, ColliderMap, laserImg, delta, player);
}
void TurretManager::Store_Turret_Wall_Location(vector<vector<int>> ColliderMap)
{
    int n_rows = ColliderMap.size();
    int n = ColliderMap[0].size();


    for (int i = 0; i < n_rows; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (ColliderMap[i][k] == wall_turret_2)
            {
                Turret_Wall newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.health = 2;
                this->Turret_Wall_location.push_back(newTurret);
            }
            else if (ColliderMap[i][k] == wall_turret_1)
            {
                Turret_Wall newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.health = 1;
                this->Turret_Wall_location.push_back(newTurret);
            }
        }
    }
}


void TurretManager::Turret_Connect(SDL_Rect camera, vector<vector<int>>& ColliderMap)
{
    int x0 = camera.x / TILE_SIZE;
    int y0 = camera.y / TILE_SIZE;
    int mapHeight = ColliderMap.size();
    int mapWidth = ColliderMap[0].size();

    bool All = true;

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
                All = true;
                int turretType = ColliderMap[gridY][gridX];  // Save turret type

                // 1) Check Down for another turret
                for (int i = gridY + 1; i < mapHeight; i++)
                {
                    if (ColliderMap[i][gridX] == turretType)  // Another turret found
                    {
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


void TurretManager::Store_Turret_Laser_Location(vector<vector<int>>& ColliderMap)
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
                this->Turret_Laser_location.push_back(newTurret);

            }
            else if (ColliderMap[i][k] == laser_turret_1)
            {
                Turret_Laser newTurret;

                newTurret.x = k;
                newTurret.y = i;
                newTurret.shot.cooldown = 2100;
                this->Turret_Laser_location.push_back(newTurret);
            }
        }
    }
}
void TurretManager::All_Turret_Shoot(SDL_Renderer* renderer, SDL_Rect camera, vector<vector<int>>& ColliderMap, SDL_Texture* laserImg, float delta, Player& player)
{
    for (auto& turret : this->Turret_Laser_location)
    {
        int map_x = turret.x * TILE_SIZE;
        int map_y = turret.y * TILE_SIZE;
        if (map_x >= camera.x - 400 && map_y >= camera.y - 400 &&
            map_x <= camera.x + SCREEN_WIDTH + 100 && map_y <= camera.y + SCREEN_HEIGHT + 100)
        {

            turret.Turret_Shoot(renderer, camera, ColliderMap, laserImg, delta, player);
        }
    }
}