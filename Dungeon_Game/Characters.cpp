#include "Characters.h"


//Bullers
void bullet::render(SDL_Renderer* renderer, SDL_Rect Dest, SDL_Texture* Bullet_Texture, bool shooting)
{
    //  Add condition that it is still shooting
    if (shooting)
        SDL_RenderCopyEx(renderer, Bullet_Texture, NULL,& Dest, angle*(180.0/M_PI)+90, NULL, SDL_FLIP_NONE); // angle clockwise
    
}

void Shoot_bullets(SDL_Renderer* renderer, bullet& shot, player_hitbox player, SDL_Texture* Bullet_Texture,vector<vector<int>> ColliderMap, float delta)
{
    int mouseX, mouseY;
    static bool shooting = false;
    static bool OnCooldown = false;

    static bool Updated_shot = true;
    
    static double acc_x;
    static double acc_y;
    
    SDL_Rect shot_hitbox;
    shot_hitbox.w = TILE_SIZE;
    shot_hitbox.h = TILE_SIZE;

    static Uint32 LastTimeRender = 0;
    static Uint32 LastTimeShot = 0;

    Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
    Uint32 currentTime = SDL_GetTicks();

    const int bullet_frame = 16; // 60fps

    if (mouseButtons && OnCooldown == false &&SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        OnCooldown = true;
        shot.x_dest = mouseX;
        shot.y_dest = mouseY;
        shooting = true;
        Updated_shot = false;
        acc_x = SCREEN_WIDTH / 2 - TILE_SIZE/2;
        acc_y = SCREEN_HEIGHT / 2 - TILE_SIZE/2;
        
    }
    if (OnCooldown && currentTime > LastTimeShot + shot.Cooldown) //Allow to shoot
    {
        LastTimeShot = currentTime;
        OnCooldown = false;
    }

    if (shooting && !Updated_shot )
    {
        shot.angle = atan2((float)shot.y_dest - SCREEN_HEIGHT / 2, (float)shot.x_dest - SCREEN_WIDTH / 2);
        shot.x_speed = (double) shot.speed * cos(shot.angle) * delta;
        shot.y_speed = (double) shot.speed * sin(shot.angle) * delta;
        Updated_shot = true;
    }


    //Animation (24 fps)
    shot_hitbox.x = round(acc_x);
    shot_hitbox.y = round(acc_y);

    if ((shooting && currentTime > LastTimeRender + bullet_frame) && !check_outofbound(shooting, shot_hitbox, shot, player, ColliderMap) )
    {
        acc_x += shot.x_speed;
        acc_y += shot.y_speed;
        LastTimeRender = currentTime;
    }

    shot.render(renderer, shot_hitbox, Bullet_Texture, shooting);
}

bool check_outofbound(bool& shooting, SDL_Rect shot_hitbox, bullet& shot, player_hitbox player, vector<vector<int>> ColliderMap)
{
    //Out of screen
    if (shot_hitbox.x > SCREEN_WIDTH || shot_hitbox.y > SCREEN_HEIGHT || shot_hitbox.x < 0 || shot_hitbox.y < 0)
    {
        shooting = false;
        return true;
    }
    
    shot.x = player.x - (SCREEN_WIDTH / 2 - shot_hitbox.x);
    shot.y = player.y - (SCREEN_HEIGHT / 2 - shot_hitbox.y);
    if (ColliderMap[shot.y / TILE_SIZE][shot.x / TILE_SIZE] == 1)
    {
        shooting = false;
        return true;
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

void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int &speed, vector <vector<int>>& ColliderMap, vector<SDL_Texture*> Animation, float delta)
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
    SDL_Delay(6);
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    int speed_x =0, speed_y = 0;
    if (keystates[SDL_SCANCODE_W]) { speed_y = -speed * delta; Moving = true; }
    if (keystates[SDL_SCANCODE_S]) { speed_y =  speed * delta; Moving = true; }
    if (keystates[SDL_SCANCODE_A]) { speed_x = -speed * delta; Moving = true; Right = false; }
    if (keystates[SDL_SCANCODE_D]) { speed_x =  speed * delta; Moving = true; Right = true;  }

    if (speed_x != 0 && speed_y != 0) //diagonal ( A W)
    {
        speed_y *= 0.7071;
        speed_x *= 0.7071;
    }
    Check_Collision(player,speed_x, speed_y, ColliderMap);

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

void Check_Collision(player_hitbox& player, int x_plus, int y_plus, vector <vector<int>>& ColliderMap)
{
    int new_x = player.x + x_plus;
    int new_y = player.y + y_plus;
    
    new_x = new_x / TILE_SIZE -1;
    new_y = new_y / TILE_SIZE -1;

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
    else { return; }

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


    if (FaceRight)
    {
        SDL_RenderCopy(renderer, Animation[CurrentFrame], NULL, &destRect);
        SDL_RenderDrawRect(renderer, &destRect);
    }
    else
    {
        SDL_RenderCopyEx(renderer, Animation[CurrentFrame], NULL, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderDrawRect(renderer, &destRect);
    }
}