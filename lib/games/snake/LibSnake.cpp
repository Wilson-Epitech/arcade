/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** snake
*/

#include "LibSnake.hpp"
#include <iostream>
#include <ostream>

arcade::LibSnake::LibSnake()
{
    init();
}

void arcade::LibSnake::init()
{
    map = {
        "###############################",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#             <==8            #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "#                             #",
        "###############################"
    };
    mapSize = 1;
    playerX = 17;
    playerY = 9;
}

std::array<std::string, 23> arcade::LibSnake::getMap()
{
    return map;
}

std::size_t arcade::LibSnake::getMapCellSize()
{
    return mapSize;
}

bool arcade::LibSnake::isAvailable(char c)
{
    if (c == '#') {
        gameStatus = arcade::LOOSE;
        return false;
    }
    return true;
}

void arcade::LibSnake::getSnakeLenght()
{
    std::size_t y = playerY;
    std::size_t x = playerX;
    size_t i = 0;
    for (; map[y][x] != '<'; i++)
        x--;
    SnakeLenght = i;

}

arcade::GameStatus arcade::LibSnake::updateMap(arcade::KeyPressed key)
{
    getSnakeLenght();
    if (key == arcade::UP) {
        std::cout << "UP" << std::endl;
    }
    if (key == arcade::DOWN) {
        std::cout << "DOWN" << std::endl;
    }
    if (key == arcade::LEFT) {
        std::cout << "LEFT" << std::endl;
    }
    if (key == arcade::RIGHT) {
        std::cout << "LEFT" << std::endl;
    }
    if (isAvailable(map.at(playerY).at(playerX + 1)) == true) {
        map[playerY][playerX - (SnakeLenght)] = ' ';
        SnakeLenght--;
        map[playerY][playerX - (SnakeLenght)] = '<';
        SnakeLenght--;
        for (; SnakeLenght != -1; SnakeLenght--)
            map[playerY][playerX - SnakeLenght] = '=';
        // map[playerY][playerX] = '=';
        map[playerY][playerX + 1] = '8';
    }
    playerX++;
    return arcade::PLAYING;
}


// fonction sens qui me donne le sens du snake
//  et faire les autres fonction tout droit pour en haut, en bas et à gauche
// fonction pour donné la pos de la tete au debut