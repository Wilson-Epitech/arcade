/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** core
*/

#include "core.hpp"

int Core::changeLibIndex(int index, int change, std::size_t nbLib)
{
    if ((index + change) < nbLib && (index + change) >= 0) {
        return (index + change);
    }
    if (index == (nbLib - 1) && change > 0) {
        return 0;
    }
    if (index == 0 && change < 0) {
        return (nbLib - 1);
    }
    return index;
}

int Core::getLibIndex(std::string path)
{
    int index = -1;
    std::vector<std::string> allGraphicalLib = _dlLoader->getGraphicalPath();
    for (int i = 0; i < NB_LIB_GRAPHICAL; i++) {
        if (path.find(allGraphicalLibraryPath[i]) != std::string::npos) {
            index = i;
        }
    }
    for (std::size_t i = 0; i < allGraphicalLib.size(); i++) {
        if (allGraphicalLib.at(i).compare(allGraphicalLibraryPath[index]) == 0) {
            return i;
        }
    }
    return -1;
}

void Core::saveScore(std::string playerName, std::string gameName, std::size_t score)
{
    if (_gameLibIndex < 0 || score <= 0 || gameName.compare("menu") == 0) {
        return;
    }
    std::string fileName = "./lib/games/score/";
    fileName.append(gameName);
    fileName.append("_score.mbw");
    std::ofstream file(fileName, std::ios::app);
    std::string scoreLine = std::to_string(score);
    scoreLine.append(" : ");
    scoreLine.append(playerName);
    scoreLine.append("\n");
    file.write(scoreLine.c_str(), strlen(scoreLine.c_str()));
    file.close();
}

void Core::changeGraphicalLib(void)
{
    _graphicalLib->stop();
    _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
    _graphicalLib = _graphicalLibAndHandler.first;
    _graphicalLib->init(_gameLib->getPattern());
    pass = 1;
}

void Core::changeGameLib(void)
{
    saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
    _gameLibAndHandler = _dlLoader->getAIGameModule(_gameLibIndex);
    _gameLib = _gameLibAndHandler.first;
    _graphicalLib->changeColor(_gameLib->getPattern());
    pass = 1;
}

void Core::changeLibrary()
{
    if (_gameLibIndex == -1) {
        return;
    }
    if (_key == arcade::N && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, 1, _libGraphicalLen);
        changeGraphicalLib();
    }
    if (_key != arcade::N && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::P && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, -1, _libGraphicalLen);
        changeGraphicalLib();
    }
    if (_key != arcade::P && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::G && pass == 0) {
        _gameLibIndex = changeLibIndex(_gameLibIndex, 1, _libGameLen);
        changeGameLib();
    }
    if (_key != arcade::G && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::M && pass == 0) {
        saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
        _gameLibIndex = -1;
        _graphicalLib->stop();
        _graphicalLib = _DefaultGraphicalLib;
        changeGameLib();
        _gameLib->initText(_dlLoader->getGraphicalPath(), _dlLoader->getGamePath());
        _graphicalLib->init(_gameLib->getPattern());
        _graphicalLib->setKey(arcade::OTHER);
    }
    if (_key != arcade::M && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::R && pass == 0) {
        _gameLib->resetGame();
        pass = 1;
    }
    if (_key != arcade::R && pass == 1) {
        pass = 0;
    }
}

Core::Core(int argc, char **argv)
{
    _dlLoader = new DlLoader;
    _graphicalLibIndex = getLibIndex(argv[1]);
    _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
    _graphicalLib = _graphicalLibAndHandler.first;
    _libGraphicalLen = _dlLoader->getGraphicalPath().size();
    _libGameLen = _dlLoader->getGamePath().size();
    if (_graphicalLibIndex == -1) {
        std::cout << "lib : " << argv[1] << " not found." << std::endl;
        exit(84);
    }

    _key = arcade::OTHER;
    _gameSpeed = 150;
    _gameLibIndex = -1;
    _gameLibAndHandler = _dlLoader->getAIGameModule(_gameLibIndex);
    _gameLib = _gameLibAndHandler.first;
    _gameLib->initText(_dlLoader->getGraphicalPath(), _dlLoader->getGamePath());
    _graphicalLib->init(_gameLib->getPattern());
    _DefaultGraphicalLib = _graphicalLib;
}

void Core::gameLoop(void)
{
    auto time1 = std::chrono::steady_clock::now();
    arcade::GameStatus status = arcade::PLAYING;
    while (status == arcade::PLAYING) {
        _graphicalLib->game(_gameLib->getGameName());
        auto time2 = std::chrono::steady_clock::now();
        auto elapsed= std::chrono::duration_cast <std::chrono::milliseconds>(time2 - time1);
        if (elapsed.count() >= _gameSpeed) {
            _key = _graphicalLib->getKey();
            if (_key == arcade::CLOSE_BUTTON) {
                break;
            }
            if (_key == arcade::BACKSPACE && _gameLib->getGameName().compare("menu") != 0) {
                _graphicalLib->stop();
                break;
            }
            if (_key == arcade::M && _gameLib->getGameName().compare("menu") == 0) {
                _graphicalLib->stop();
                break;
            }
            status = _gameLib->updateMap(_key);
            if (_gameLibIndex == -1 && _key == arcade::ENTER) {
                playerName = _graphicalLib->getPlayerName();
                if (playerName.size() < 1) {
                    playerName = "DefaultPlayer";
                }
                std::pair<std::size_t, std::size_t> indexPair = _gameLib->getIndexes();
                _gameLibIndex = indexPair.second;
                _graphicalLibIndex = indexPair.first;
                changeGraphicalLib();
                changeGameLib();
            } 
            changeLibrary();
            _graphicalLib->setKey(arcade::OTHER);
            time1 = std::chrono::steady_clock::now();
        }
        _graphicalLib->displayMap(_gameLib->getMap(), _gameLib->getMapCellSize());
        if (status == arcade::WON_AND_RELOADED) {
            status = arcade::PLAYING;
            _gameLib->resetGame();
            _gameSpeed -= 15;
        }
        _graphicalLib->displayText(_gameLib->getText());
        if (status == arcade::LOOSE) {
            status = arcade::PLAYING;
            _graphicalLib->setKey(arcade::OTHER);
            _key = arcade::M;
            changeLibrary();
        }
    }
    saveScore(playerName, _gameLib->getGameName(), _gameLib->getScore());
}

void displayUsage(void)
{
    std::cout << "./arcade [Lib]" << std::endl << std::endl;
    std::cout << "[Lib] :\tpath to the graphical library used at the start of arcade" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        displayUsage();
        return 84;
    }
    Core core(argc, argv);

    core.gameLoop();
    return 0;
}
