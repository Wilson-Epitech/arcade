/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibPacman
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "../../IGameModule.hpp"
#include "../../Color.hpp"
#include "../../KeyPressed.hpp"
#include "../../GameStatus.hpp"

namespace arcade {
    class LibSnake : virtual public arcade::IGameModule {
        public:
            LibSnake();
            ~LibSnake() {};
            void resetGame() override {};
            std::array<std::string, 23> getMap() override;
            std::map<std::string, Color> getPattern() override {};
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::size_t getMapCellSize() override;
        protected:
        private:
            bool isAvailable(char c);
            void getSnakeLenght();
            void init();
            std::size_t playerX;
            std::size_t playerY;
            std::size_t mapSize;
            GameStatus gameStatus;
            std::size_t SnakeLenght;
            std::array<std::string, 23> map;
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibSnake);
    }
}

#endif /* !LIBPACMAN_HPP_ */