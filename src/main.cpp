/*
** ARCADE PROJECT, 2024
** graphical
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string>
#include "../lib/graphical/IDisplayModule.hpp"
#include "../lib/graphical/KeyPressed.hpp"
#include <gnu/lib-names.h>
#include <iostream>

std::pair <arcade::IDisplayModule *,void *> entryPoint(void)
{
    void *handle;
    arcade::IDisplayModule * (*do_somthing)(void);
    char *err;

    //handle = dlopen("./lib/arcade_sfml.so", RTLD_LAZY);
    handle = dlopen("./lib/arcade_sdl.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    do_somthing = (arcade::IDisplayModule * (*)(void)) dlsym(handle, "entrypoint");
    err = dlerror();
    if (err != NULL) {
        fprintf(stderr, "%s\n", err);
        exit(EXIT_FAILURE);
    }
    return {(*do_somthing)(), handle};
}

int main(void)
{
    std::pair <arcade::IDisplayModule *,void *> lib = entryPoint();
    arcade::IDisplayModule *lib_graphical = lib.first;
    std::array<std::string, 19UL> map = {
        "######################################",
        "##    []      []      []      []    ##",
        "##  ######  ##  ######  ##  ######  ##",
        "##[]##  ##[]##          ##[]##  ##[]##",
        "##  ######  ##  ##  ##  ##  ######  ##",
        "##          ##[]##  ##[]##          ##",
        "##  ##########  ##  ##  ##########  ##",
        "##[]##  []                  []  ##[]##",
        "##  ##  ########      ########  ##  ##",
        "##      []                  []      ##",
        "##  ##########  ######  ##########  ##",
        "##    []        ##  ##        []    ##",
        "##  ######  ##  ######  ##  ######  ##",
        "##  ##  ##  ##          ##  ##  ##  ##",
        "##[]######[]##[]######[]##[]######[]##",
        "##          ##  ##  ##  ##          ##",
        "##[]##########  ######  ##########[]##",
        "##          <=========8~            ##",
        "######################################"
    };
    while (!lib_graphical->game()) {
        lib_graphical->textDisplay("Arcade", 50, 10);
        lib_graphical->displayMap(map);
        if (lib_graphical->getKey() == arcade::DOWN) {
            std::cout << "key down\n";
        }
    }

    return 0;
}
