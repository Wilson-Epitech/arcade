/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** SaveScore
*/

#include "saveScore.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

arcade::Error::Error(const std::string& errorMessage)
    : _errorMessage(errorMessage) {}

const char *arcade::Error::what() const noexcept
{
    return this->_errorMessage.c_str();
}

arcade::SaveScore::SaveScore()
{
}

void arcade::SaveScore::getPlayerName(std::string playerName)
{
    _playerName = playerName;
}

void arcade::SaveScore::getGameName(std::string gameName)
{
    _gameName = gameName;
}

void arcade::SaveScore::getScore(size_t score)
{
    _score = score;
}

void arcade::SaveScore::setFileName()
{
    _fileName = _gameName + ("_score.mwb");
}

std::string arcade::SaveScore::setFilePath(std::string _fileName)
{
    // std::string filePath = "lib/games/score/" + _fileName;
    std::string filePath = _fileName;
    return filePath;
}

int arcade::SaveScore::saveIntoFile()
{
    std::string str = _playerName + " - " + std::to_string(_score) + " pts\n";
    std::string filePath = setFilePath(_fileName);
    std::ofstream file(filePath, std::ios::app);

    if (file.is_open()) {
        file.write(str.c_str(), strlen(str.c_str()));
        file.close();
    } else {
        throw arcade::Error("Impossible to open the file");
        return 84;
    }
    return 0;
}

// int main(void)
// {
//     arcade::SaveScore scoreSaver;

//     std::string player_name = "Wilson";
//     std::string game_name = "Pacman";
//     size_t score = 100;

//     scoreSaver.getPlayerName(player_name);
//     scoreSaver.getGameName(game_name);
//     scoreSaver.getScore(score);
//     scoreSaver.setFileName();
//     scoreSaver.saveIntoFile();
// }