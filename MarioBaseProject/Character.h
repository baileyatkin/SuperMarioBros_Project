#pragma once
#include "SDL.h"
#include "Commons.h"
#include <iostream>
#include <string>
#include "Texture2D.h"
#include "constants.h"
#include "LevelMap.h"

using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_current_level_map;
	bool m_moving_right;
	bool m_moving_left;
	bool m_can_jump;
	bool m_jumping;
	bool m_alive;
	float m_jump_force;
	float m_collision_radius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	void AddGravity(float deltaTime);
	float GetCollisionRadius();
	bool IsJumping()
	{
		if (m_jumping)
		{
			return true;
		}
		return false;
	}
	void CancelJump()
	{
		m_jumping = false;
	}
	CollisionCircle CreateCollisionCircle()
	{
		return CollisionCircle(m_position.x, m_position.y, m_collision_radius);
	}
	Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}
	void SetAlive(bool isAlive)
	{
		m_alive = isAlive;
	}
	bool GetAlive()
	{
		return m_alive;
	}


private:
	FACING m_facing_direction;
};