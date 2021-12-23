#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "TimeManager.h"

#include <stdlib.h>
#include <time.h>

class Enemy
{
	const float powerUpTime = 5;
	float powerUp_countdown;
	const float spawnTime = 5;
	float spawn_countdown;
	COORD spawn;
	COORD position;
	COORD direction;
	char character;
	ConsoleUtils::CONSOLE_COLOR background;
	ConsoleUtils::CONSOLE_COLOR foreground;

	ConsoleUtils::CONSOLE_COLOR foreground_powerUp;
	ConsoleUtils::CONSOLE_COLOR foreground_noPowerUp;
	void RandomDirection();
public:
	enum ENEMY_STATE { ENEMY_NORMAL, ENEMY_EATED, ENEMY_KILLED };
	Enemy();
	Enemy(COORD _spawn, float _spawn_countdown = 5);
	void PowerUpPicked();
	ENEMY_STATE Update(Map* _map, COORD playerPos);
	void Kill();
	void Draw();
};

