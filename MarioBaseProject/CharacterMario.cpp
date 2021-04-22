#include "CharacterMario.h"
#include "Texture2D.h"
#include "constants.h"

using namespace std;

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_moving_left = false;
	m_moving_right = false;
	m_can_jump = true;
	m_facing_direction = FACING_RIGHT;
	m_jumping = false;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

CharacterMario::~CharacterMario()
{
	m_renderer = nullptr;
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = true;
				break;
			case SDLK_RIGHT:
				m_moving_right = true;
				break;
			case SDLK_UP:
				if (m_can_jump)
				{
					Jump();
				}
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_moving_left = false;
				break;
			case SDLK_RIGHT:
				m_moving_right = false;
				break;
			}
			break;
		}
	Character::Update(deltaTime, e);
}
