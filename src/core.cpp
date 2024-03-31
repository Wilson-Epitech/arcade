/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** core
*/

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
#include "core.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <deque>
#include <unistd.h>
#include <chrono>

bool isALib (std::string path) {
    if (path.size() < 5) {
        return false;
    }
    std::string tmp;
    for (int i = path.size() - 1; i > (path.size() - 4); i--) {
        path.erase(i, 0);
        tmp.push_back(path.at(i));
    }
    if (tmp.compare("os.") == 0) {
        return true;
    }
    return false;
}

std::deque<std::string> allLibAvailable (void)
{
    DIR *dir;
    struct dirent *en;
    dir = opendir("./lib/");
    std::deque<std::string> path;
    if (dir) {
        while ((en = readdir(dir)) != NULL) {
            if (isALib(en->d_name) == true)
                path.push_back(en->d_name);
        }
        closedir(dir);
    }
    return path;
}

std::deque <std::pair <arcade::IDisplayModule *,void *>> entryPoint2(std::deque<std::string> path)
{
    std::deque <std::pair <arcade::IDisplayModule *,void *>> allLib;
    for (int i = 0; i < path.size(); i++) {
        void *handle;
        arcade::IDisplayModule * (*do_somthing)(void);
        char *err;
        std::string realPath = "./lib/";
        realPath.append(path.at(i));
        handle = dlopen(realPath.c_str() , RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "ooo%s\n", dlerror());
            exit(84);
        }
        dlerror();
        do_somthing = (arcade::IDisplayModule * (*)(void)) dlsym(handle, "entryPoint");
        err = dlerror();
        if (err != NULL) {
            fprintf(stderr, "ddd%s\n", dlerror());
            continue;
        }
        allLib.push_back({(*do_somthing)(), handle});
        allLib.at(allLib.size() - 1).first->stop();
    }
    return allLib;
}

std::pair <arcade::IDisplayModule *,void *> entryPoint(std::string libPath)
{
    void *handle;
    arcade::IDisplayModule * (*do_somthing)(void);
    char *err;

    handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    dlerror();
    do_somthing = (arcade::IDisplayModule * (*)(void)) dlsym(handle, "entryPoint");
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "%s\n", err);
        exit(84);
    }
    return {(*do_somthing)(), handle};
}

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


int getUsedLib(const char *path)
{
    int index = 0;
    while (index < NB_LIB) {
        if (strcmp(path, allLibraryPath[index].c_str()) == 0) {
            return index;
        }
        index++;
    }
    return 0;
}

int changeLibIndex(int index, int change)
{
    if ((index + change) < NB_LIB && (index + change) >= 0) {
        return (index + change);
    }
    if (index == (NB_LIB - 1) && change > 0) {
        return 0;
    }
    if (index == 0 && change < 0) {
        return (NB_LIB - 1);
    }
    return index;
}

int main(int argc, char **argv)
{
    //entryPoint2(allLibAvailable());
    //std::cout << "pass\n";

    std::pair <arcade::IDisplayModule *,void *> lib = entryPoint(argv[1]);
    std::pair <arcade::IGameModule *,void *> gameLib = entryPointGame();
    int libIndex = getUsedLib(argv[1]);
    arcade::IDisplayModule *lib_graphical = lib.first;
    arcade::IGameModule *libGame = gameLib.first;
    auto time1 = std::chrono::steady_clock::now();
    arcade::KeyPressed key = arcade::OTHER;
    arcade::GameStatus status = arcade::PLAYING;
    lib_graphical->init(libGame->getPattern());
    int gameSpeed = 150;

    while (status == arcade::PLAYING) {
        lib_graphical->game();
        //lib_graphical->displayText(libGame->getText());
        auto time2 = std::chrono::steady_clock::now();
        auto elapsed= std::chrono::duration_cast <std::chrono::milliseconds>(time2 - time1);

        if (elapsed.count() >= gameSpeed) {
            key = lib_graphical->getKey();
            if (key == arcade::CLOSE_BUTTON) {
                return 0;
            }
            status = libGame->updateMap(key);
            time1 = std::chrono::steady_clock::now();
        }
        lib_graphical->displayMap(libGame->getMap(), libGame->getMapCellSize());
        if (status == arcade::WON_AND_RELOADED) {
            status = arcade::PLAYING;
            libGame->resetGame();
            gameSpeed -= 15;

        }
     }
    dlclose(lib.second);
    dlclose(gameLib.second);
    return 0;
}
