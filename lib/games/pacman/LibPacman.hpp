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
#include <chrono>

namespace arcade {
    class LibPacman : virtual public arcade::IGameModule {
        public:
            LibPacman();
            ~LibPacman() {};
            void resetGame() override {};
            std::array<std::string, 23> getMap() override;
            std::map<std::string, Color> getPattern() override {};
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::size_t getMapCellSize() override;
        private:
            void init();
            int findPlayer();
            void updateKeyPressed(arcade::KeyPressed key);
            bool isAvailable(char c);
            void moovePlayer(arcade::KeyPressed key);
            bool tpPlayerSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changePlayerPos(arcade::KeyPressed key);
            void moovePlayerBis(arcade::KeyPressed key);
            void addScore(char c);
            void changeGhostState(void);
            void isGameWin(void);

            void launchMooveGhost();
            void getNexGhost();
            bool tpGhostSide(arcade::KeyPressed key, int defaultX, int defaultY);
            void changeGhostPos(arcade::KeyPressed key);
            bool isAvailableDirect(int x, int y);
            arcade::KeyPressed randKey(arcade::KeyPressed key1, arcade::KeyPressed key2, arcade::KeyPressed key3);
            arcade::KeyPressed changeGhostKey(arcade::KeyPressed key);
            arcade::KeyPressed mooveGhost(arcade::KeyPressed key);
            bool isAvailableGhost(char c);
            void wallBoxGhost(void);

            std::array<std::string, 23> map;
            std::size_t mapSize;
            std::size_t playerX;
            std::size_t playerY;
            GameStatus gameStatus;
            KeyPressed keyPressed;
            KeyPressed keyPressedGhost;
            int score;
            bool pacBuff;
            std::chrono::_V2::steady_clock::time_point timeEatBuff;

            std::size_t ghostX;
            std::size_t ghostY;
            std::array<arcade::KeyPressed, 4> keyGhost = {arcade::UP, arcade::UP, arcade::UP, arcade::UP};
            std::array<std::pair<std::pair<std::size_t, std::size_t>, char>, 4> ghostPos;
            int tt;
            
            std::chrono::_V2::steady_clock::time_point timeStart;
    };
}


#endif /* !LIBPACMAN_HPP_ */
