#include "GameUI.h"


void InGameUI::Init(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("UI_Elements/fonts/Arial.ttf", 60);

	PlayerBarBackground = LoadTexture("UI_Elements/PlayerBar/Background.png", renderer);
	for (int i = 0;i <= 6; i++)
	{
		string ImageName = "UI_Elements/PlayerBar/Revolver_" + to_string(i) + ".png";
		RevolverAmmo.push_back(LoadTexture(ImageName, renderer));
	}
	this ->PlayerBarRect = { 20, 20, 320, 140 };
	this ->PlayerHPRect = { 100, 40, 220, 35 };
	this ->RevolverRect = { 110, 80, 60, 60 };
	this ->PlayerHP_NumRect = { 175, 40, 60, 35 };
	this ->Ammo_NumRect = { 200, 80, 35, 60 };
}

void InGameUI::RenderPlayerBar(SDL_Renderer* renderer, const Player& player)
{
	SDL_RenderCopy(renderer, PlayerBarBackground, NULL, &PlayerBarRect);
	//HP Bar
	int temp_width = PlayerHPRect.w;
	PlayerHPRect.w *= (float) player.hp / player.MaxHp;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &PlayerHPRect); // HP bar

	PlayerHPRect.w = temp_width;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &PlayerHPRect); // Outline

	SDL_Color textColor = { 0, 0, 0 }; // Black text

	string HpNum = to_string(player.hp) + "/" + to_string(player.MaxHp);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, HpNum.c_str(), textColor);
	SDL_Texture* NumText = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(renderer, NumText, NULL, &PlayerHP_NumRect);

	//Revolver
	static string AmmoNum;
	static int lastAmmo = -1;  // Store last ammo count to detect changes
	
	if (player.bullets.ammo != lastAmmo)  // Update only if ammo changes
	{
		lastAmmo = player.bullets.ammo;  // Store current ammo for future comparison

		if (player.bullets.ammo == 0)
		{
			Ammo_NumRect.x = 185;
			Ammo_NumRect.w = 125;
			AmmoNum = "Reloading";
		}
		else if (player.bullets.ammo > 6)
		{
			Ammo_NumRect.x = 185;
			Ammo_NumRect.w = 125;
			AmmoNum = "Infinite";
		}
		else
		{
			Ammo_NumRect.x = 200;
			Ammo_NumRect.w = 35;
			AmmoNum = to_string(player.bullets.ammo);
		}
	}

	textSurface = TTF_RenderText_Solid(font, AmmoNum.c_str(), textColor);
	NumText = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, NumText, NULL, &Ammo_NumRect);
	if (player.bullets.ammo > 6)
	{
		SDL_RenderCopy(renderer, RevolverAmmo[6], NULL, &RevolverRect);
	}
	else
	{
		SDL_RenderCopy(renderer, RevolverAmmo[player.bullets.ammo], NULL, &RevolverRect);
	}

	//Can add a minimap
}