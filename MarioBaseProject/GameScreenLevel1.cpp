#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "constants.h"
#include "PowBlock.h"
#include <ctime>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	m_renderer = renderer;
	spawn_timer = 10.0f;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	delete mario_character;
	delete luigi_character;
	mario_character = nullptr;
	luigi_character = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//update character
	if (mario_character->GetAlive())
		mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);
	
	spawn_timer -= deltaTime;
	if (spawn_timer <= 0.0f)
	{
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 96.0f);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, 96.0f);
		spawn_timer = 10.0f;
	}
	
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);

	//check for circle collisions
	if (Collisions::Instance()->Circle(mario_character->CreateCollisionCircle(), luigi_character->CreateCollisionCircle()))
	{
		cout << "Circle hit!" << endl;
	}

	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(), luigi_character->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//render character
	if (mario_character->GetAlive())
		mario_character->Render();
	luigi_character->Render();

	//render PowBlock
	m_pow_block->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//set up level map
	SetLevelMap();

	//set up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(192, 330), m_level_map);

	//set up enemies
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, 96.0f);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, 96.0f);
	
	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[13][16] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
						{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
						{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;


}

void GameScreenLevel1::UpdatePowBlock()
{
	if ((Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), mario_character->GetCollisionBox())) && (m_pow_block->IsAvailable()))
	{
		//collided while jumping
		if (mario_character->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			mario_character->CancelJump();
		}
	}

}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = 0.25f;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH -
					(float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);

			}
			//now do the update
			m_enemies[i]->Update(deltaTime, e);

				//check to see if enemy collides with player
				if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x
				> SCREEN_WIDTH - 96.0f))
				{
					//ignored collisions if behind pipe
				}
				else
				{
					if (Collisions::Instance()->Circle(m_enemies[i]->CreateCollisionCircle(), mario_character->CreateCollisionCircle()))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
						}
						else
						{
							mario_character->SetAlive(false);
						}
					}
				}

				//if the enemy is no longer alive then schedule it for deletion
				if (!m_enemies[i]->GetAlive())
				{
					enemyIndexToDelete = i;
				}
		}
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(koopa);
}