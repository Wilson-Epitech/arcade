/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <stdio.h>
    #include <stdlib.h>
    #include <dlfcn.h>
    #include <string>
    #include <string.h>
    #include "../lib/includes/IDisplayModule.hpp"
    #include "../lib/includes/KeyPressed.hpp"
    #include "../lib/includes/IGameModule.hpp"
    #include "../lib/includes/Color.hpp"
    #include <gnu/lib-names.h>
    #include <iostream>
    #include <dirent.h>
    #include <sys/types.h>
    #include <deque>
    #include <unistd.h>
    #include <chrono>
    #include "dlLoader.hpp"

class Core {
    public:
        Core(int argc, char **argv);
        ~Core() {};
        void gameLoop(void);
    private:
        arcade::IDisplayModule *_graphicalLib;
        arcade::IGameModule *_gameLib;
        std::vector<std::string> _allGamePath;
        std::vector<std::string> _allGraphicalPath;
        std::pair <arcade::IDisplayModule *,void *> _graphicalLibAndHandler;
        std::pair <arcade::IGameModule *,void *> _gameLibAndHandler;
        std::size_t _libGraphicalLen;
        std::size_t _libGameLen;
        int _graphicalLibIndex;
        int _gameLibIndex;
        arcade::KeyPressed _key;
        int _gameSpeed;
        DlLoader *_dlLoader;
        int pass = 0;

        int getLibIndex(std::string path);
        void changeLibrary();
        int changeLibIndex(int index, int change, std::size_t nbLib);
};



#endif /* !CORE_HPP_ */
