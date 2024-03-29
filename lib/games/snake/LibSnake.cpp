/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** snake
*/

#include <vector>
#include "LibSnake.hpp"
#include <iostream>
#include <ostream>
#include <functional>
#include <utility>
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
    direction = DROITE;
    SnakeLenght = 4;
    getQueue();
    size_t y = queueY;
    size_t x = queueX;
    for (int i = 0; i < SnakeLenght; i++)
        MyVector.push_back(std::make_pair(1, 2));
    for(int i = 0; i < MyVector.size(); i++) {
         MyVector[i].first = y;
         MyVector[i].second = x;
         x++;
     }
}

std::array<std::string, 23> arcade::LibSnake::getMap()
{
    return map;
}

std::size_t arcade::LibSnake::getMapCellSize()
{
    return mapSize;
}

int arcade::LibSnake::findPlayer()
{
    size_t y = 0;
    size_t x = 0;
    size_t y_map = 20;
    size_t x_map = 31;

    for (y = 0; y != y_map; y++) {
        for(x = 0; x != x_map; x++)
            if (map[y][x] == '8') {
                playerY = y;
                playerX = x;
            }
    }
}

void arcade::LibSnake::getQueue()
{
    size_t y = 0;
    size_t x = 0;
    size_t y_map = 20;
    size_t x_map = 31;

    for (y = 0; y != y_map; y++) {
        for(x = 0; x != x_map; x++)
            if (map[y][x] == '<') {
                queueY = y;
                queueX = x;
            }
    }
}

bool arcade::LibSnake::isAvailable(char c)
{
    if (c == '#')
        return false;
    if (c == '<')
        return false;
    if (c == '=')
        return false;
    return true;
}

void arcade::LibSnake::getSnakeLenght()
{
    if (MyVector.empty() == false)
        SnakeLenght = MyVector.size();
}

void arcade::LibSnake::updateKeyPressed(arcade::KeyPressed key)
{
    if (key != arcade::OTHER) {
        keyPressed = key;
    }
}

std::map<std::string, arcade::Color> arcade::LibSnake::getPattern()
{
    std::map<std::string, arcade::Color> pattern;
    pattern.insert({" ", arcade::BLACK});
    pattern.insert({"#", arcade::GRAY});
    pattern.insert({"o", arcade::WHITE});
    pattern.insert({"O", arcade::CYAN});
    pattern.insert({"|", arcade::BLACK});
    pattern.insert({"8", arcade::BLUE});
    pattern.insert({"=", arcade::GREEN});
    pattern.insert({"<", arcade::GREEN});
    return pattern;
}

void arcade::LibSnake::moovePlayer(arcade::KeyPressed key)
{
};

arcade::GameStatus arcade::LibSnake::updateMap(arcade::KeyPressed key)
{
    findPlayer();
    getSnakeLenght();
    getQueue();
    if (key == arcade::RIGHT && (direction != GAUCHE && direction != DROITE)) {
        if (isAvailable(map.at(playerY).at(playerX + 1)) == true) {
        direction = DROITE;
            playerX++;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].second++;
        } else return arcade::LOOSE;
    }

    if (key == arcade::UP && (direction != BAS && direction != HAUT)) {
        if (isAvailable(map.at(playerY - 1).at(playerX)) == true) {
        direction = HAUT;
            playerY--;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].first--;
        } else return arcade::LOOSE;
    }
    if (key == arcade::DOWN && (direction != HAUT && direction != BAS)) {
        if (isAvailable(map.at(playerY + 1).at(playerX)) == true) {
        direction = BAS;
            playerY++;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].first++;
        } else return arcade::LOOSE;
    }
    if (key == arcade::LEFT && (direction != DROITE  && direction != GAUCHE)) {
        if (isAvailable(map.at(playerY).at(playerX - 1)) == true) {
        direction = GAUCHE;
            playerX--;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].second--;
        } else return arcade::LOOSE;
    }
    if (direction == DROITE) {
            if (isAvailable(map.at(playerY).at(playerX + 1)) == true) {
            playerX++;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].second++;
        } else return arcade::LOOSE;
    }
    if (direction == GAUCHE) {
            if (isAvailable(map.at(playerY).at(playerX - 1)) == true) {
            playerX--;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].second--;
        } else return arcade::LOOSE;
    }


    if (direction == BAS) {
            if (isAvailable(map.at(playerY + 1).at(playerX)) == true) {
            playerY++;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].first++;
        } else return arcade::LOOSE;
    }

    if (direction == HAUT) {
            if (isAvailable(map.at(playerY - 1).at(playerX)) == true) {
            playerY--;
            map[playerY][playerX] = '8';
            map[MyVector[0].first][MyVector[0].second] = ' ';
            for(int i = 0; i < (MyVector.size() - 1); i++) {
                MyVector[i].first = MyVector[i + 1].first;
                MyVector[i].second = MyVector[i + 1].second;
                }
            map[MyVector[0].first][MyVector[0].second] = '<';
            for(int i = 1; i < (MyVector.size() - 1); i++) {
                map[MyVector[i].first][MyVector[i].second] = '=';
                }
            MyVector[SnakeLenght - 1].first--;
        } else return arcade::LOOSE;
    }
    return arcade::PLAYING;
}