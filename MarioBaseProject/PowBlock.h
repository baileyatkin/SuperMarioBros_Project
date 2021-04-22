#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include "constants.h"
#include "LevelMap.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	void TakeHit();
	bool IsAvailable() 
	{
		return m_num_hits_left > 0;
	};
	Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
};

