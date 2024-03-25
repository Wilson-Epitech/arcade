/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibPacman
*/

#include "LibPacman.hpp"

arcade::LibPacman::LibPacman()
{
    init();
}

void arcade::LibPacman::init()
{
    map = {
        "###############################",
        "#oooooooooooooo##ooooooooooooo#",
        "#o####o#######o##o######o####o#",
        "#O####o#######o##o######o####O#",
        "#ooooooooooooooooooooooooooooo#",
        "#o####o##o###########o##o####o#",
        "#o####o##oooooo##ooooo##o####o#",
        "#oooooo#######o##o######oooooo#",
        "######o##ooooooooooooo##o######",
        "######o##o#####  ####o##o######",
        "######o##o#### M  ###o##o######",
        "#ooooooooo####M  M###ooooooooo#",
        "#o####o##o###########o##o####o#",
        "#Ooo##oooooooooPooooooooo##ooO#",
        "###o##o##o###########o##o##o###",
        "#oooooo##oooooo##ooooo##oooooo#",
        "#o############o##o###########o#",
        "#o############o##o###########o#",
        "#ooooooooooooooooooooooooooooo#",
        "###############################"
    };
    mapSize = 1;
    playerX = 0;
    playerY = 0;
}

std::array<std::string, 21> arcade::LibPacman::getMap()
{
    return map;
}

std::size_t arcade::LibPacman::getSize()
{
    return mapSize;
}

int arcade::LibPacman::findPlayer()
{
    playerX = 0;
    playerY = 0;
    while (playerY < map.size()) {
        while (playerX < map.at(playerY).size()) {
            if (map.at(playerY).at(playerX) == 'P') {
                return 0;
            }
            playerX++;
        }
        playerX = 0;
        playerY++;
    }
    return 84;
}

bool arcade::LibPacman::isAvailable(char c)
{
    switch (c) {
        case '#':
            return false;
        case '=':
            return false;
        case '<':
            return false;
        default:
            break;
    }
}

arcade::GameStatus arcade::LibPacman::updateMap(arcade::KeyPressed key)
{
    findPlayer();
    if (key == arcade::UP) {
        playerY - 1;
    }
    if (key == arcade::DOWN) {
        playerY + 1;
    }
    if (key == arcade::LEFT) {
        playerX - 1;
    }
    if (key == arcade::RIGHT) {
        playerX + 1;
    }

    return arcade::PLAYING;
}

//map.at(playerY).at(playerX)