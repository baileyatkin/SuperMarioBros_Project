#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed)
	: Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_renderer = renderer;
	m_injured = false;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
	m_renderer = nullptr;
}

void CharacterKoopa::TakeDamage()
{
	cout << "DAMAGE TAKEN" << endl;
	m_injured = true;
	m_injured_time = 2.5f;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (m_facing_direction == FACING_LEFT)
		m_facing_direction = FACING_RIGHT;
	else
		m_facing_direction = FACING_LEFT;

	m_injured = false;
	Jump();

}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (m_injured)
		left = m_single_sprite_w;

	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w,m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightwayUp();
	}
}

bool CharacterKoopa::GetInjured()
{
	cout << m_injured << endl;
	return m_injured;
}

void CharacterKoopa::TurnAround()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction == FACING_RIGHT;
		m_moving_right = true;
		m_moving_left = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction == FACING_LEFT;
		m_moving_right = false;
		m_moving_left = true;
	}
}
