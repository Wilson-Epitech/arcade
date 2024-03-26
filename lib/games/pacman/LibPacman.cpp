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
        "###oooo##o####   ####o##oooo###",
        "###o##o##o### M M ###o##o##o###",
        "|ooooooooo### M M ###ooooooooo|",
        "#o####o######     ######o####o#",
        "|ooooooooo###     ###ooooooooo|",
        "#o####o##o###########o##o####o#",
        "#Ooo##oooooooooPooooooooo##ooO#",
        "###o##o##o###########o##o##o###",
        "#oooooo##oooooo##ooooo##oooooo#",
        "#o############o##o###########o#",
        "#o############o##o###########o#",
        "#ooooooooooooooooooooooooooooo#",
        "###############################"
    };
    tt = 0;
    mapSize = 1;
    playerX = 0;
    playerY = 0;
    gameStatus = arcade::PLAYING;
    keyPressed = arcade::OTHER;
    keyPressedGhost = arcade::UP;
    score = 0;
    timeStart = std::chrono::steady_clock::now();
    timeEatBuff = std::chrono::steady_clock::now();
    pacBuff = false;
}

std::array<std::string, 23> arcade::LibPacman::getMap()
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
        return false;
    }
    return true;
}

void arcade::LibPacman::updateKeyPressed(arcade::KeyPressed key)
{
    if (key != arcade::OTHER) {
        keyPressed = key;
    }
}

void arcade::LibPacman::changeGhostState(void)
{
    auto timeNow = std::chrono::steady_clock::now();
    auto timeElapsed= std::chrono::duration_cast <std::chrono::milliseconds>(timeNow - timeEatBuff);
    if (timeElapsed.count() < 5000) {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map.at(i).size(); j++) {
                if (map.at(i).at(j) == 'M') {
                    map.at(i).at(j) = 'F';
                }
            }
        }
    } else {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map.at(i).size(); j++) {
                if (map.at(i).at(j) == 'F') {
                    map.at(i).at(j) = 'M';
                }
            }
        }
    }
}

void arcade::LibPacman::isGameWin(void)
{
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == 'o' || map.at(i).at(j) == 'O') {
                return;
            }
        }
    }
    gameStatus = arcade::WON;
}

arcade::GameStatus arcade::LibPacman::updateMap(arcade::KeyPressed key)
{
    if (key == arcade::QUITE) {
        return arcade::QUIT;
    }
    findPlayer();
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.at(i).size(); j++) {
            if (map.at(i).at(j) == 'F') {
                map.at(i).at(j) = 'M';
            }
        }
    }
    launchMooveGhost();
    changeGhostState();
    moovePlayer(key);
    return gameStatus;
}

bool arcade::LibPacman::tpPlayerSide(arcade::KeyPressed key, int defaultX, int defaultY)
{
    if (playerX >= map.at(playerY).size() && key == arcade::RIGHT) {
        map[defaultY][defaultX] = '|';
        playerX = 0;
        map[playerY][playerX] = 'P';
        return true;
    }
    if (isAvailable(map.at(playerY).at(playerX)) == true) {
        if (playerX == 0 && key == arcade::LEFT) {
            map[defaultY][defaultX] = '|';
            playerX = map.at(playerY).size() - 1;
            map[playerY][playerX] = 'P';
            return true;
        }
    }
    return false;
}

void arcade::LibPacman::changePlayerPos(arcade::KeyPressed key)
{
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
}

void arcade::LibPacman::moovePlayer(arcade::KeyPressed key)
{
    int defaultX = playerX;
    int defaultY = playerY;
    changePlayerPos(key);
    if (tpPlayerSide(key, defaultX, defaultY) == true) {
        return;
    }
    if (isAvailable(map.at(playerY).at(playerX)) == true) {
        addScore(map.at(playerY).at(playerX));
        map[defaultY][defaultX] = ' ';
        map[playerY][playerX] = 'P';
        updateKeyPressed(key);
    } else {
        playerX = defaultX;
        playerY = defaultY;
        moovePlayerBis(keyPressed);
    }
    playerX = 0;
    playerY = 0;
}

void arcade::LibPacman::moovePlayerBis(arcade::KeyPressed key)
{
    int defaultX = playerX;
    int defaultY = playerY;
    changePlayerPos(key);
    if (tpPlayerSide(key, defaultX, defaultY) == true) {
        return;
    }
    if (isAvailable(map.at(playerY).at(playerX)) == true) {
        addScore(map.at(playerY).at(playerX));
        map[defaultY][defaultX] = ' ';
        map[playerY][playerX] = 'P';
    }
}

void arcade::LibPacman::addScore(char c)
{
    if (c == 'o') {
        score += 10;
    }
    if (c == 'O') {
        score += 50;
        timeEatBuff = std::chrono::steady_clock::now();
        pacBuff = true;
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map.at(i).size(); j++) {
                if (map.at(i).at(j) == 'M') {
                    map.at(i).at(j) = 'F';
                }
            }
        }
    }
    if (c == 'F') {
        score += 200;
        map.at(10).at(15) = 'M';
    }
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibPacman);
    }
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::LibPacman::getText()
{
    std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay;
    textToDisplay.push_back({"Pacman", {10, 10}});
    std::string scoreTxt;
    scoreTxt = "Score : ";
    scoreTxt.append(std::to_string(score));
    textToDisplay.push_back({scoreTxt, {200, 10}});
    return textToDisplay;
}
