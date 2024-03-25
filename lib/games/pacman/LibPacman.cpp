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
        "#Ooo##oooPooooooooooooooo##ooO#",
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
    gameStatus = arcade::PLAYING;
    keyPressed = arcade::OTHER;
}

std::array<std::string, 21> arcade::LibPacman::getMap()
{
    return map;
}

std::size_t arcade::LibPacman::getMapCellSize()
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
    if (c == '#') {
        return false;
    }
    if (c == 'M') {
        gameStatus = arcade::LOOSE;
    }
    return true;
}

void arcade::LibPacman::updateKeyPressed(arcade::KeyPressed key)
{
    if (key != arcade::OTHER) {
        keyPressed = key;
    }
}

void arcade::LibPacman::moovePlayer(arcade::KeyPressed key)
{
    int defaultX = playerX;
    int defaultY = playerY;
    if (key == arcade::UP) {
        playerY -= 1;
    }
    if (key == arcade::DOWN) {
        playerY += 1;
    }
    if (key == arcade::LEFT) {
        playerX -= 1;
    }
    if (key == arcade::RIGHT) {
        playerX += 1;
    }

    if (isAvailable(map.at(playerY).at(playerX)) == true) {
        map[defaultY][defaultX] = ' ';
        map[playerY][playerX] = 'P';
    }
}

arcade::GameStatus arcade::LibPacman::updateMap(arcade::KeyPressed key)
{
    findPlayer();
    int defaultX = playerX;
    int defaultY = playerY;
    if (key == arcade::UP) {
        playerY -= 1;
    }
    if (key == arcade::DOWN) {
        playerY += 1;
    }
    if (key == arcade::LEFT) {
        playerX -= 1;
    }
    if (key == arcade::RIGHT) {
        playerX += 1;
    }
    if (isAvailable(map.at(playerY).at(playerX)) == true) {
        map[defaultY][defaultX] = ' ';
        map[playerY][playerX] = 'P';
        updateKeyPressed(key);
    } else {
        playerX = defaultX;
        playerY = defaultY;
        moovePlayer(keyPressed);
    }
    playerX = 0;
    playerY = 0;
    return gameStatus;
}
