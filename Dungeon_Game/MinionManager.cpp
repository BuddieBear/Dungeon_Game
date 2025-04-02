#include "MinionManager.h"

MinionManager::~MinionManager()
{
	SDL_DestroyTexture(this->Melee);
}

void MinionManager::GetMelee_Minion(vector<vector<int>>& ColliderMap, SDL_Texture* Melee_Text, const SDL_Rect& camera)
{ 
	this->Melee = Melee_Text;

	int n_rows = ColliderMap.size();
	int n = ColliderMap[0].size();

	for (int i = 0; i < n_rows; i++)
	{
		for (int k = 0; k < n;k++)
		{
			if (ColliderMap[i][k] == Minion_Spawn)
			{
				Melee_Minion CurrentMinion;
				CurrentMinion.Init(k * TILE_SIZE, i * TILE_SIZE, camera);
				ColliderMap[i][k] = 0;
				this->Melee_Location.push_back(CurrentMinion);
			}
		}
	}
}


void MinionManager::Run_Melee_Minion(SDL_Renderer* renderer, const SDL_Rect& camera, Player& player, vector<vector<int>>& ColliderMap, const float& delta)
{
	for (auto& Minion : Melee_Location)
	{
		if (Minion.x > camera.x && Minion.y > camera.y && Minion.x < camera.x + SCREEN_WIDTH && Minion.y < camera.y + SCREEN_HEIGHT)
		{
			Minion.Run(renderer, camera, player, this->Melee, ColliderMap, delta);
		}
	}
}
