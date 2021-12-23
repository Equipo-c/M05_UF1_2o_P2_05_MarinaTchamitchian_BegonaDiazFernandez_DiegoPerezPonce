// Main.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//





// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


#include "Map.h"
#include "Enemy.h"
#include "TimeManager.h"
#include <vector>
#include "CustomVector.h"
#include "Player.h"


using namespace std;

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
            cout << "BIEN HECHO" << endl;
            cout << "Pulsa 'Q' para salir" << endl;
            system("PAUSE");
            win = true;
        }


        for (size_t i = 0; i < enemies.size(); i++)
        {
            switch (enemies[i].Update(&pacman_map, player.position))
                // switch (enemies[i].Update(&pacman_map, { (short)player_x , (short)player_y }))
            {
            case Enemy::ENEMY_STATE::ENEMY_EATED:
                player.position.X = pacman_map.spawn_player.X;
                player.position.Y = pacman_map.spawn_player.Y;
                //^ el enemigo nos mata
                player.life--;

                break;
            case Enemy::ENEMY_STATE::ENEMY_KILLED:
                //se lo come el player
                enemies[i].Kill();
                player.points += 50;
                break;
            default:
                break;
            }
        }
        if (player.life <= 0) {
            //lanzamos en consola GameOver
            ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
            std::cout << "Has perdido" << std::endl;
            cout << "Pulsa 'Q' para salir" << endl;
            system("PAUSE");
        }
    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0, 0);
    pacman_map.Draw();

    player.Draw();
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << player.points << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    std::cout << "vidas: " << player.life << std::endl;

    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }

    std::cout << TimeManager::getInstance().frameCount << std::endl;
    std::cout << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << TimeManager::getInstance().time << std::endl;

    TimeManager::getInstance().NextFrame();
}