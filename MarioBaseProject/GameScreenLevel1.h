#pragma once
#ifndef _GAMESCREEN1_H
#define _GAMESCREEN1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include <vector>
#include "CharacterKoopa.h"

class Character;
class Texture2D;
class PowBlock;
class CharacterKoopa;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
	CharacterKoopa* koopa;
	CollisionCircle* mario_collisions;
	CollisionCircle* luigi_collisions;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	vector<CharacterKoopa*> m_enemies;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float spawn_timer;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock();
};

#endif _GAMESCREEN1_H

