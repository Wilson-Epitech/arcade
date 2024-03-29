/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibPacman
*/

#include "LibMenu.hpp"

arcade::LibMenu::LibMenu()
{
}

void arcade::LibMenu::initText(std::vector<std::string> gameLibName, std::vector<std::string> graphicalName)
{
    _gameLibName = gameLibName;
    _graphicalName = graphicalName;
}

void arcade::LibMenu::resetGame()
{
}

std::array<std::string, 23> arcade::LibMenu::getMap()
{
}

std::size_t arcade::LibMenu::getMapCellSize()
{
}

arcade::GameStatus arcade::LibMenu::updateMap(arcade::KeyPressed key)
{
}

std::vector<std::pair<std::string, std::pair<int, int>>> arcade::LibMenu::getText()
{
    std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay;
    int x = 50;
    int y = 50;
    for (std::size_t i = 0; i < _gameLibName.size(); i++) {
        textToDisplay.push_back({_gameLibName.at(i), {x, y}});
        y += 50;
    }
    y = 50;
    for (std::size_t i = 0; i < _graphicalName.size(); i++) {
        textToDisplay.push_back({_graphicalName.at(i), {x, y}});
        x += 50;
    }
    return textToDisplay;
}

std::map<std::string, arcade::Color> arcade::LibMenu::getPattern()
{
    std::map<std::string, arcade::Color> pattern;
    pattern.insert({" ", arcade::BLACK});
    pattern.insert({"#", arcade::GRAY});
    pattern.insert({"o", arcade::WHITE});
    pattern.insert({"O", arcade::CYAN});
    pattern.insert({"|", arcade::BLACK});
    pattern.insert({"M", arcade::RED});
    pattern.insert({"P", arcade::YELLOW});
    pattern.insert({"F", arcade::BLUE});
    return pattern;
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibMenu);
    }
}
