/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibPacman
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "../../includes/IGameModule.hpp"
#include "../../includes/Color.hpp"
#include "../../includes/KeyPressed.hpp"
#include "../../includes/GameStatus.hpp"

namespace arcade {
    class LibSnake : virtual public arcade::IGameModule {
        public:
            LibSnake();
            ~LibSnake() {};
            void resetGame() override {};
            std::array<std::string, 23> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::size_t getMapCellSize() override;
            void initText(std::vector<std::string>, std::vector<std::string>) override {};
            std::pair<std::size_t, std::size_t> getIndexes() override {};
        protected:
        private:
            void getQueue();
            int findPlayer();
            void updateKeyPressed(arcade::KeyPressed key);
            bool isAvailable(char c);
            bool isAvailableFood(char c);
            void getSnakeLenght();
            void init();
            int moovePlayer(arcade::KeyPressed Key);
            int moove();
            int changePlayerPos(std::string str);
            void placeFood();
            void fillVector();
            std::vector<std::pair<int, int>> MyVector;
            KeyPressed keyPressed;
            std::size_t queueY;
            std::size_t queueX;
            std::size_t playerX;
            std::size_t playerY;
            std::size_t mapSize;
            GameStatus gameStatus;
            std::size_t SnakeLenght;
            std::array<std::string, 23> map;
            enum Direction {
                DROITE,
                HAUT,
                GAUCHE,
                BAS
                };
            Direction direction;
            size_t score;
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibSnake);
    }
}

#endif /* !LIBPACMAN_HPP_ */