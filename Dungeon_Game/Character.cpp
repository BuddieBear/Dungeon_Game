#include "Character.h"


//Bullets
void revolver::render(SDL_Renderer* renderer, SDL_Rect Dest, SDL_Texture* Bullet_Texture, bool shooting)
{
    //  Add condition that it is still shooting
    if (shooting)
    {
        SDL_RenderCopyEx(renderer, Bullet_Texture, NULL, &Dest, angle*(180.0/M_PI)+90, NULL, SDL_FLIP_NONE); // angle clockwise
        SDL_RenderDrawRect(renderer, &Dest); //hitbox
    }
    
}

void Shoot_bullets(SDL_Renderer* renderer, revolver& shot, player_hitbox player, SDL_Texture* Bullet_Texture,vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, float delta, SDL_Rect camera)
{
    int mouseX, mouseY;
    static bool shooting = false;
    static bool OnCooldown = false;
    static bool EmptyMag = false;
    static bool Updated_shot = true;
    static bool JustPress = false;
   
    SDL_Rect shot_hitbox; // On screen only
    shot_hitbox.w = TILE_SIZE;
    shot_hitbox.h = TILE_SIZE;

    static Uint32 LastTimeRender = 0;
    static Uint32 LastTimeShot = 0;

    Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
    Uint32 currentTime = SDL_GetTicks();

    if (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT) && !OnCooldown && !EmptyMag && !JustPress)
    {

        shot.x_dest = mouseX;
        shot.y_dest = mouseY;
        shooting = true;
        Updated_shot = false;
        OnCooldown = true;
        JustPress = true;

        shot.ammo -= 1;

        shot.x = player.x - TILE_SIZE/2;
        shot.y = player.y - TILE_SIZE/2;
    }
    else
    {
        JustPress = false;
    }

    if (shot.ammo == 0)
    {
        EmptyMag = true;
    }

    if (OnCooldown && EmptyMag == false && currentTime > LastTimeShot + shot.Cooldown) //Allow to shoot with ammo left
    {
        LastTimeShot = currentTime;
        OnCooldown = false;
    }

    if (EmptyMag && currentTime > LastTimeShot + shot.ReloadTime)
    {
        LastTimeShot = currentTime;
        EmptyMag = false;
        shot.ammo = shot.MaxAmmo;   
    }


    if (shooting && !Updated_shot )
    {
        shot.angle = atan2((float)shot.y_dest - SCREEN_HEIGHT / 2, (float)shot.x_dest - SCREEN_WIDTH / 2);
        shot.x_speed = (double) shot.speed * cos(shot.angle) * delta;
        shot.y_speed = (double) shot.speed * sin(shot.angle) * delta;
        Updated_shot = true;
    }


    //Animation
    shot_hitbox.x = shot.x - camera.x;
    shot_hitbox.y = shot.y - camera.y;

    if ((shooting && currentTime > LastTimeRender + bullet_frame) && !Check_BulletHit(shooting, shot_hitbox, shot, player, ColliderMap, TurretWallLocation, Laser_Turrets) )
    {
        shot.x += shot.x_speed;
        shot.y += shot.y_speed;
        LastTimeRender = currentTime;
    }

    shot.render(renderer, shot_hitbox, Bullet_Texture, shooting);
}

bool Check_BulletHit(bool& shooting, SDL_Rect shot_hitbox, revolver& shot, player_hitbox player, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets)
{
    //Out of screen
    if (shot_hitbox.x > SCREEN_WIDTH || shot_hitbox.y > SCREEN_HEIGHT || shot_hitbox.x < 0 || shot_hitbox.y < 0)
    {
        shooting = false;
        return true;
    }
   
    int a = shot.x / TILE_SIZE;
    int b = shot.y / TILE_SIZE;

    int tile_n = ColliderMap[b][a];

    //Collisions
    if (tile_n == 1) // Walls
    {
        shooting = false;
        return true;
    }
    else if (Check_Surrounding_Bullet(shot, box, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet(shot, wall_turret_1, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet(shot, wall_turret_2, a, b, ColliderMap, TurretWallLocation, Laser_Turrets))
    {
        shooting = false;
        return true;
    }
    else if (Check_Surrounding_Bullet(shot, laser_turret_1, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet(shot, laser_turret_2, a, b, ColliderMap, TurretWallLocation, Laser_Turrets)) // shoot laser turret
    {
        shooting = false;
        return true;
    }
    else return false;
}
bool Check_Surrounding_Bullet(revolver shot, int n_decal, int a, int b, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets)
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
                    if (n_decal == wall_turret_2 || n_decal == wall_turret_1) // if hit wall
                    {
                        for (auto& turret : TurretWallLocation) // Check Health
                        {
                            if (turret.x  == checkX && turret.y  == checkY) // find it in the TurretWallLocation
                            {
                                if (turret.health == 1)
                                {
                                    ColliderMap[checkY][checkX] = 0;
                                    turret.health = 0;
                                    //Destroing Ajacent FireWalls
                                        //Up
                                    for (int i = checkY-1; i >= 0; i--)
                                    {
                                        if (ColliderMap[i][checkX] == wall_fire)
                                        {
                                            ColliderMap[i][checkX] = 0;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                        //Down
                                    for (int i = checkY + 1; i < mapHeight; i++)
                                    {
                                        if (ColliderMap[i][checkX] == wall_fire)
                                        {
                                            ColliderMap[i][checkX] = 0;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                        //Left
                                    for (int k = checkX - 1; k >= 0; k--)
                                    {
                                        if (ColliderMap[checkY][k] == wall_fire)
                                        {
                                            ColliderMap[checkY][k] = 0;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                        //Right
                                    for (int k = checkX + 1; k < mapWidth; k++)
                                    {
                                        if (ColliderMap[checkY][k] == wall_fire)
                                        {
                                            ColliderMap[checkY][k] = 0;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    cerr << "Turret was destroyed" << endl;
                                }
                                else if (turret.health == 2)
                                {
                                    cerr << "Damaged" << endl;
                                    turret.health = 1;
                                }
                                break;
                            }
                        }
                    }  
                    else
                    {
                        if (n_decal == laser_turret_1 || n_decal == laser_turret_2)
                        {
                            int n = 0;
                            for (auto& LTurret : Laser_Turrets)
                            {
                                
                                if (LTurret.x == checkX && LTurret.y == checkY)
                                {
                                    Laser_Turrets.erase(Laser_Turrets.begin() +n);
                                    break;
                                }
                                n++;
                            }
                        }
                        ColliderMap[checkY][checkX] = 0;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// players
void LoadAnimation(vector<SDL_Texture*>& Animation_pack, SDL_Renderer* renderer)
{
    for (int i = 0; i < 8; i++)
    {
        string Animation_file = "Characters/Cowboy/Walk/Walk (" + to_string(i + 1) + ").png";
        Animation_pack.push_back(LoadTexture(Animation_file, renderer));
        cerr << Animation_file << endl;
    }
}

void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int &speed, vector <vector<int>>& ColliderMap, vector<SDL_Texture*> Animation, float delta, SDL_Rect& camera, bool& player_alive)
{
    int Cycle_Frame = 8; // 8 images
    static Uint32 LastFrame =0; // Track time for animation
    static int CurrentFrame = 0;
    static int n = 0;
    
    static bool Right = true;

    SDL_Event event;
    bool Moving = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
    }
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    int speed_x =0, speed_y = 0;
    if (keystates[SDL_SCANCODE_W]) { speed_y = -speed * delta; Moving = true; }
    if (keystates[SDL_SCANCODE_S]) { speed_y =  speed * delta; Moving = true; }
    if (keystates[SDL_SCANCODE_A]) { speed_x = -speed * delta; Moving = true; Right = false; }
    if (keystates[SDL_SCANCODE_D]) { speed_x =  speed * delta; Moving = true; Right = true;  }

    if (speed_x != 0 && speed_y != 0) //diagonal ( A+W)
    {
        speed_y *= 0.7071;
        speed_x *= 0.7071;
    }
    Check_Collision(player,speed_x, speed_y, ColliderMap, camera, player_alive);

    //Animation (24 fps) 
    Uint32 currentTime = SDL_GetTicks(); 
    if (Moving && currentTime > LastFrame + Delay_Frame) 
    {
        CurrentFrame = (CurrentFrame + 1) % Cycle_Frame; // Cycle through frames
        LastFrame = currentTime;
    }
    //Updates frames
    RenderCharacter(Animation, renderer, CurrentFrame, Right);
}

void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap, SDL_Rect& camera, bool& player_alive)
{
    int new_x = player.x + x_plus;
    int new_y = player.y + y_plus;
    
    new_x = new_x / TILE_SIZE  ;
    new_y = new_y / TILE_SIZE  ;

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
        //Tuong tu
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
    else if (tile_num == wall_fire || tile_num == wall_turret_1 || tile_num == wall_turret_2 || tile_num == laser_turret_1 || tile_num == laser_turret_2)
    {
        player_alive = false;
    }
    else { return; }

    camera.x = player.x - SCREEN_WIDTH / 2;
    camera.y = player.y - SCREEN_HEIGHT / 2;

    player.x = player.x + x_plus;
    player.y = player.y + y_plus;
    return;
}

void RenderCharacter( vector<SDL_Texture*> Animation, SDL_Renderer* renderer, int CurrentFrame, bool FaceRight)
{

    SDL_Rect destRect;
    destRect.h = p_size;
    destRect.w = p_size;

    destRect.x = SCREEN_WIDTH / 2 - p_size/2;
    destRect.y = SCREEN_HEIGHT / 2 - p_size/2;


    if (FaceRight) // >D
    {
        SDL_RenderCopy(renderer, Animation[CurrentFrame], NULL, &destRect);
        SDL_RenderDrawRect(renderer, &destRect);
    }
    else // A<
    {
        SDL_RenderCopyEx(renderer, Animation[CurrentFrame], NULL, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderDrawRect(renderer, &destRect);
    }
}

