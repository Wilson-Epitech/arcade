/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibPacman
*/

#ifndef LIBPACMAN_HPP_
#define LIBPACMAN_HPP_

#include "../../IGameModule.hpp"
#include "../../Color.hpp"
#include "../../KeyPressed.hpp"
#include "../../GameStatus.hpp"
#include <string>
#include <iostream>

namespace arcade {
    class LibPacman : virtual public arcade::IGameModule {
        public:
            LibPacman();
            ~LibPacman() {};
            void resetGame() override {};
            std::array<std::string, 21> getMap() override;
            std::map<std::string, Color> getPattern() override {};
            std::vector<std::string> getText() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            KeyPressed nextPlayerMove() override {};
            std::size_t getSize() override;
            bool isAvailable(char c) override;
        private:
            void init();
            int findPlayer();

            std::array<std::string, 21> map;
            size_t mapSize;
            int playerX;
            int playerY;
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibPacman);
    }
}


#endif /* !LIBPACMAN_HPP_ */
