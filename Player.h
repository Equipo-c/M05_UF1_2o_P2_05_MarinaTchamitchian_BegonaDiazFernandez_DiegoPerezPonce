#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "Enemy.h"
#include <vector>
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

class Player
{
	COORD playerSpawn;
	COORD playerDirection;
	char playerChar;
	ConsoleUtils::CONSOLE_COLOR playerBackground;
	ConsoleUtils::CONSOLE_COLOR playerForeground;

public:
	int lives = 3;  //kill restar vidas
	COORD playerPosition;
	int playerPoints = 0;
	Player(COORD _spawn);
	void Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies);
	//void playerInput();
	void DrawPlayer();
};

