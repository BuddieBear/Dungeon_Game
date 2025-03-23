#include "SDL_Utils.h"

using namespace std;

void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Surface*& surface)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cerr, "SDL_Init", true);

    window = SDL_CreateWindow("Soul Noob (Dungeon game)", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);


    if (window == nullptr)
        logSDLError(std::cerr, "CreateWindow", true);

    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
        logSDLError(std::cerr, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //surface
    surface = SDL_GetWindowSurface(window);
    if (surface == nullptr)
        logSDLError(std::cout, "GetWindowSurface", true);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* LoadTexture(const std::string imgfile, SDL_Renderer* renderer)
{
    SDL_Texture* Loaded_Texture = nullptr;
    SDL_Surface* New_Surface = IMG_Load(imgfile.c_str() );
    //check failed surface 
    if (New_Surface == nullptr) logSDLError(std::cerr, "Cannot load New_Surface for texture", false);

    Loaded_Texture = SDL_CreateTextureFromSurface(renderer, New_Surface);
    //check failed Texture
    if (Loaded_Texture == nullptr || New_Surface == nullptr)
    {
        logSDLError(std::cerr, "Cannot load Texture: " + imgfile, false);
        return nullptr;
    }
    return Loaded_Texture;
}

bool CheckCollisionRect(const SDL_Rect& a, const SDL_Rect& b)
{
    return (a.x < b.x + b.w && // so sanh _-
        a.x + a.w > b.x &&
        a.y < b.y + b.h && // so sanh  ||
        a.y + a.h > b.y);
}
