#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "TimeManager.h"
#include <vector>

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();


Map pacman_map = Map();
std::vector<Enemy> enemies;
Player player = Player(pacman_map.spawn_player);
USER_INPUTS input = USER_INPUTS::NONE;
bool run = true;
bool win = false;
bool lose = false;

int main()
{
    Setup();
    while (run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);

    srand(time(NULL));

    int totalEnemies = 0;
    std::cout << "Cuantos enemigos quieres? ";
    std::cin >> totalEnemies;
    if (totalEnemies < 1)
        totalEnemies = 1;
    for (size_t i = 0; i < totalEnemies; i++)
    {
        enemies.push_back(Enemy(pacman_map.spawn_enemy, 5.0f * i));
    }

}

void Input()
{
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        USER_INPUTS::QUIT;
    }
    input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
      if (win)
      {
          switch (input)
          {
          case QUIT:
              run = false;
              break;
          }
      }
      else
      {
          switch (input)
          {
          case QUIT:
              run = false;
              break;
          }
          player.Update(&pacman_map, input, &enemies);
          
          if (pacman_map.points <= 0)
          {
               win = true;
          }


           for (size_t i = 0; i < enemies.size(); i++)
           {
               switch (enemies[i].Update(&pacman_map, player.playerPosition))
               {
               case Enemy::ENEMY_STATE::ENEMY_EATED:
                   player.playerPosition.X = pacman_map.spawn_player.X;
                   player.playerPosition.Y = pacman_map.spawn_player.Y;
                   player.lives--;
                   break;
               case Enemy::ENEMY_STATE::ENEMY_KILLED:
                   enemies[i].Kill();
                   player.playerPoints += 50;
                   break;
               default:
                   break;
               }
           }
           if (player.lives <= 0) {
               lose = true;
               run = false;
           }
      }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    pacman_map.Draw();
    player.DrawPlayer();
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Vidas: " << player.lives << std::endl;
    std::cout << "Puntuacion actual: " << player.playerPoints << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
        std::cout << "Pulsa 'Q'para salir." << std::endl;
    }
    if (lose)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::WHITE);
        std::cout << "Has perdido!" << std::endl;
    }

    /*std::cout << TimeManager::getInstance().time << std::endl;*/
    /*std::cout << TimeManager::getInstance().frameCount << std::endl;
    std::cout << TimeManager::getInstance().deltaTime << std::endl;*/

    TimeManager::getInstance().NextFrame();
}
