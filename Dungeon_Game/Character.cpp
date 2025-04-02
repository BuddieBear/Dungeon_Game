#include "Character.h"


//Bullets
revolver::~revolver()
{
    SDL_DestroyTexture(this->Img);
}
void revolver::get_revolver(SDL_Texture* bulletimg)
{
    shot_hitbox.w = TILE_SIZE;
    shot_hitbox.h = TILE_SIZE;
    Img = bulletimg;
}

void revolver::render(SDL_Renderer* renderer, const SDL_Rect& Dest)
{
    //  Add condition that it is still shooting
    if (shooting)
    {
        SDL_RenderCopyEx(renderer, Img, NULL, &Dest, angle*(180.0/M_PI)+90, NULL, SDL_FLIP_NONE); // angle clockwise
        SDL_RenderDrawRect(renderer, &Dest); //hitbox
    }
    
}

void revolver::Shoot_bullets(SDL_Renderer* renderer, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, const float& delta, const SDL_Rect& camera, bool JustShot)
{
    int mouseX, mouseY;
    Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
    Uint32 currentTime = SDL_GetTicks();

    if (ammo == 0)
    {
        EmptyMag = true;
    }

    if (JustShot && !OnCooldown && !EmptyMag)
    {
        this ->x_dest = mouseX;
        this ->y_dest = mouseY;
        shooting = true;
        Updated_shot = false;
        OnCooldown = true;


        this ->x = camera.x + SCREEN_WIDTH/2 - TILE_SIZE/2;
        this ->y = camera.y + SCREEN_HEIGHT/2 - TILE_SIZE/2;
    }


    if (OnCooldown && EmptyMag == false && currentTime > LastTimeShot + Cooldown) //Allow to shoot with ammo left
    {
        LastTimeShot = currentTime;
        OnCooldown = false;
    }

    if (EmptyMag && currentTime > LastTimeShot + ReloadTime)
    {
        LastTimeShot = currentTime;
        EmptyMag = false;
        ammo = MaxAmmo;   
    }

    if (shooting && !Updated_shot)
    {
        angle = atan2((float)this->y_dest - SCREEN_HEIGHT / 2, (float)this->x_dest - SCREEN_WIDTH / 2);
        this->x_speed = (double)speed * cos(angle) * delta;
        this->y_speed = (double)speed * sin(angle) * delta;
        Updated_shot = true;

        if (ammo > 0)
        {
            ammo -= 1;
        }
    }

    //Animation
    shot_hitbox.x = this ->x - camera.x;
    shot_hitbox.y = this ->y - camera.y;

    if ((shooting && currentTime > LastTimeRender + bullet_frame) && !Check_BulletHit(ColliderMap, TurretWallLocation, Laser_Turrets) )
    {
        this ->x += x_speed;
        this ->y += y_speed;
        LastTimeRender = currentTime;
    }

    this ->render(renderer, shot_hitbox);
}

bool revolver::Check_BulletHit(vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets)
{
    //Out of screen
    if (shot_hitbox.x > SCREEN_WIDTH || shot_hitbox.y > SCREEN_HEIGHT || shot_hitbox.x < 0 || shot_hitbox.y < 0)
    {
        shooting = false;
        return true;
    }
   
    int a = this->x / TILE_SIZE;
    int b = this->y / TILE_SIZE;

    int tile_n = ColliderMap[b][a];

    //Collisions
    if (tile_n == 1) // Walls
    {
        shooting = false;
        return true;
    }
    else if (Check_Surrounding_Bullet(box, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet( wall_turret_1, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet(wall_turret_2, a, b, ColliderMap, TurretWallLocation, Laser_Turrets))
    {
        shooting = false;
        return true;
    }
    else if (Check_Surrounding_Bullet(laser_turret_1, a, b, ColliderMap, TurretWallLocation, Laser_Turrets) || Check_Surrounding_Bullet(laser_turret_2, a, b, ColliderMap, TurretWallLocation, Laser_Turrets)) // shoot laser turret
    {
        shooting = false;
        return true;
    }
    else return false;
}

// can optimize furthur
bool revolver::Check_Surrounding_Bullet(int n_decal, int a, int b, vector<vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets)
{
    SDL_Rect TempTile = { 0, 0, TILE_SIZE, TILE_SIZE };
    SDL_Rect shotOnMap = { this->x - TILE_SIZE / 2, this->y - TILE_SIZE / 2, TILE_SIZE, TILE_SIZE };

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

                if (CheckCollisionRect(shotOnMap, TempTile))
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

void Player::PlayerInit(SDL_Texture* playerText, SDL_Texture* BulletText, SDL_Renderer* renderer)
{
    player_box = { SCREEN_WIDTH / 2 - p_size / 2, SCREEN_HEIGHT / 2 - p_size / 2, p_size, p_size };
    this->Img = playerText;
    this->bullets.get_revolver(BulletText);
    this->LoadAnimation(renderer);
}

Player::~Player()
{
    SDL_DestroyTexture(this->Img);
    for (auto tex : this->Walk_Animation) SDL_DestroyTexture(tex);
}

void Player::LoadAnimation( SDL_Renderer* renderer)
{
    for (int i = 0; i < 8; i++)
    {
        string Animation_file = "Characters/Cowboy/Walk/Walk (" + to_string(i + 1) + ").png";
        this->Walk_Animation.push_back(LoadTexture(Animation_file, renderer));
    }
}

void Player::Handle_Movement(SDL_Renderer* renderer, vector <vector<int>>& ColliderMap, vector<Turret_Wall>& TurretWallLocation, vector<Turret_Laser>& Laser_Turrets, const float& delta, SDL_Rect& camera)
{
    /*if (this->hp == 0)
    {
        this->alive = false;
        return;
    }*/ // long

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
            this->alive = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            this->bullets.Shoot_bullets(renderer, ColliderMap, TurretWallLocation, Laser_Turrets, delta, camera, true);
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
    Check_Collision(speed_x, speed_y, ColliderMap, camera);

    //Animation (24 fps) 
    Uint32 currentTime = SDL_GetTicks(); 
    if (Moving && currentTime > LastFrame + Delay_Frame) 
    {
        CurrentFrame = (CurrentFrame + 1) % Cycle_Frame; // Cycle through frames
        LastFrame = currentTime;
    }
    //Updates frames
    RenderCharacter(renderer, CurrentFrame, Right);
}
void Player::Check_Collision(int x_plus, int y_plus, vector<vector<int>>& ColliderMap, SDL_Rect& camera)
{
    int new_x = this->x + x_plus;
    int new_y = this->y + y_plus;
    // Check the new position in tile coordinates
    int tile_x = new_x / TILE_SIZE;
    int tile_y = new_y / TILE_SIZE;

    // Create the hitbox for the new position BEFORE moving
    SDL_Rect NewHitbox = { new_x - 24 / 2, new_y - 36 / 2, 24, 36 };
    
    // Check collision BEFORE updating the position
    if (Check_Surrounding_Player(NewHitbox, tile_x, tile_y, ColliderMap)) 
    {
        return; // Collision detected, don't move
    }

    // Update the player's position ONLY if no collision
    this->x = new_x;
    this->y = new_y;

    // Update camera position to follow player
    camera.x = this->x - SCREEN_WIDTH / 2;
    camera.y = this->y - SCREEN_HEIGHT / 2;
}

bool Player::Check_Surrounding_Player(const SDL_Rect& NewHitbox, int new_x, int new_y, vector<vector<int>>& ColliderMap)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int k = -1; k <= 1; k++)
        {
            int x0 = new_x + i;
            int y0 = new_y + k;
            int TileNum = ColliderMap[y0][x0];
            if (TileNum != 0 && TileNum != Opened_wood_chest)
            {
                SDL_Rect TempTile = { x0 * TILE_SIZE + TILE_SIZE/2, y0 * TILE_SIZE , TILE_SIZE, TILE_SIZE };
                if (CheckCollisionRect(NewHitbox, TempTile))
                {
                    if (TileNum == silver_key)
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
                    else if (TileNum == gold_key)
                    {
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
                    else if (TileNum == victory_crown)
                    {
                        this->win = true;
                        this->alive = false;
                    }
                    else if (TileNum == Unopened_wood_chest)
                    {
                        int odd = rand() % 10;
                        ColliderMap[y0][x0] = Opened_wood_chest;

                        if ( odd <3 ) // 30%
                        {
                            cerr << "Reward: Speed boost" << endl;
                            this->speed *= 1.25;
                        }
                        else if (odd == 3) // 10%
                        {
                            cerr << "Reward: 1Mil bullets" << endl;
                            this->bullets.MaxAmmo = 1000000;
                            this->bullets.ammo = 1000000;
                        }
                        else if (odd < 6)  // 20%
                        {
                            cerr << "Reward: +5 Max Health" << endl;
                            this->MaxHp += 5;
                            this->hp = this-> MaxHp;
                        }
                        else if (odd < 8) // 20%
                        {
                            cerr << "Reward: Fast FireRate" << endl;
                            this->bullets.Cooldown *= 0.8;
                        }
                        else // 20%
                        {
                            cerr << "Debuff: Fatigue" << endl;
                            this->speed *= 0.8;  // 1.25x slower
                            this->bullets.Cooldown *= 1.25;  // 1.25x slower
                        }
                    }
                    else if (TileNum == wall_fire || TileNum == wall_turret_1 || TileNum == wall_turret_2 || TileNum == laser_turret_1 || TileNum == laser_turret_2)
                    {
                        this->alive = false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::RenderCharacter(  SDL_Renderer* renderer, int CurrentFrame, bool FaceRight)
{

    SDL_Rect destRect;
    destRect.h = p_size;
    destRect.w = p_size;

    destRect.x = SCREEN_WIDTH / 2 - p_size/2;
    destRect.y = SCREEN_HEIGHT / 2 - p_size/2;

    if (FaceRight) // >D
    {
        SDL_RenderCopy(renderer, Walk_Animation[CurrentFrame], NULL, &destRect);
    }
    else // A<
    {
        SDL_RenderCopyEx(renderer, Walk_Animation[CurrentFrame], NULL, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
}
