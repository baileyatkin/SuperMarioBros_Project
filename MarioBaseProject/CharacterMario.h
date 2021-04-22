#pragma once
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e) override;

private:
	FACING m_facing_direction;
};

