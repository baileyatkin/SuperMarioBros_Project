#pragma once
#include "Character.h"

class CharacterKoopa : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;
	FACING m_facing_direction;

	void FlipRightwayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	bool GetInjured();
	void TurnAround();
	bool HittingScreenBounds();
};

