#include "Characters.h"

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

void Handle_Movement(bool& running, SDL_Renderer* renderer, player_hitbox& player, const int &speed, vector <vector<int>>& ColliderMap, vector<SDL_Texture*> Animation)
{
    static Uint32 LastFrame =0; // Track  time for animation
    static int CurrentFrame = 0;
    static int n = 0;
    int Cycle_Frame = 8; // 8 images

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
    if (keystates[SDL_SCANCODE_W]) { speed_y = -speed; Moving = true; }
    if (keystates[SDL_SCANCODE_S]) { speed_y =  speed; Moving = true; }
    if (keystates[SDL_SCANCODE_A]) { speed_x = -speed; Moving = true; }
    if (keystates[SDL_SCANCODE_D]) { speed_x =  speed; Moving = true; }

    if (speed_x != 0 && speed_y != 0) //diagonal ( A W)
    {
        speed_y *= 0.7071;
        speed_x *= 0.7071;
    }
    Check_Collision(player,speed_x, speed_y, ColliderMap);

    Uint32 currentTime = SDL_GetTicks();

    if (Moving && currentTime > LastFrame + Delay_Frame) 
    {
        CurrentFrame = (CurrentFrame + 1) % Cycle_Frame; // Cycle through frames
        LastFrame = currentTime;
    }
    //Updates frames
    RenderCharacter(Animation, renderer, CurrentFrame);
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

void RenderCharacter( vector<SDL_Texture*> Animation, SDL_Renderer* renderer, int CurrentFrame)
{

    SDL_Rect destRect;
    destRect.h = p_size;
    destRect.w = p_size;

    destRect.x = SCREEN_WIDTH / 2 - p_size;
    destRect.y = SCREEN_HEIGHT / 2 - p_size;

    SDL_RenderCopy(renderer, Animation[CurrentFrame], NULL, &destRect);
}