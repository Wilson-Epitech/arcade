/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** core
*/

#include "core.hpp"

std::pair <arcade::IGameModule *,void *> entryPointGame(void)
{
    void *handle;
    arcade::IGameModule * (*do_somthing)(void);
    char *err;

    handle = dlopen("./lib/arcade_snake.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    do_somthing = (arcade::IGameModule * (*)(void)) dlsym(handle, "entryPoint");
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "%s\n", err);
        exit(84);
    }
    return {(*do_somthing)(), handle};
}


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

void Core::changeLibrary()
{
    if (_key == arcade::N && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, 1, _libGraphicalLen);
        _graphicalLib->stop();
        dlclose(_graphicalLibAndHandler.second);
        _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
        _graphicalLib = _graphicalLibAndHandler.first;
        _graphicalLib->init(_gameLib->getPattern());
        pass = 1;
    }
    if (_key != arcade::N && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::P && pass == 0) {
        _graphicalLibIndex = changeLibIndex(_graphicalLibIndex, -1, _libGraphicalLen);
        _graphicalLib->stop();
        dlclose(_graphicalLibAndHandler.second);
        _graphicalLibAndHandler = _dlLoader->getAIDisplayModule(_graphicalLibIndex);
        _graphicalLib = _graphicalLibAndHandler.first;
        _graphicalLib->init(_gameLib->getPattern());
        pass = 1;
    }
    if (_key != arcade::P && pass == 1) {
        pass = 0;
    }
    if (_key == arcade::G && pass == 0) {
        _gameLibIndex = changeLibIndex(_gameLibIndex, 1, _libGameLen);
        _gameLib->resetGame();
        dlclose(_gameLibAndHandler.second);
        _gameLibAndHandler = _dlLoader->getAIGameModule(_gameLibIndex);
        _gameLib = _gameLibAndHandler.first;
        _graphicalLib->init(_gameLib->getPattern());
        pass = 1;
    }
    if (_key != arcade::G && pass == 1) {
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

    _gameLibAndHandler = entryPointGame();
    _gameLib = _gameLibAndHandler.first;
    _key = arcade::OTHER;
    _gameSpeed = 150;
    _graphicalLib->init(_gameLib->getPattern());
}

void Core::gameLoop(void)
{
    auto time1 = std::chrono::steady_clock::now();
    arcade::GameStatus status = arcade::PLAYING;
    while (status == arcade::PLAYING) {
        _graphicalLib->game(" ");
        auto time2 = std::chrono::steady_clock::now();
        auto elapsed= std::chrono::duration_cast <std::chrono::milliseconds>(time2 - time1);
        if (elapsed.count() >= _gameSpeed) {
            _key = _graphicalLib->getKey();
            if (_key == arcade::CLOSE_BUTTON) {
                exit(0);
            }
            changeLibrary();
            status = _gameLib->updateMap(_key);
            time1 = std::chrono::steady_clock::now();
        }
        _graphicalLib->displayMap(_gameLib->getMap(), _gameLib->getMapCellSize());
        if (status == arcade::WON_AND_RELOADED) {
            status = arcade::PLAYING;
            _gameLib->resetGame();
            _gameSpeed -= 15;

        }
        _graphicalLib->displayText(_gameLib->getText());
    }
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