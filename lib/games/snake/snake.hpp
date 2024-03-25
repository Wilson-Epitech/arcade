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
            std::array<std::string, 19> getMap() override {};
            std::map<std::string, Color> getPattern() override {};
            std::vector<std::string> getText() override {};
            GameStatus updateMap(arcade::KeyPressed key) override {};
            KeyPressed nextPlayerMove() override {};
            std::size_t getSize() override {};
        protected:    
        private:
            void init();
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibSnake);
    }
}

#endif /* !LIBPACMAN_HPP_ */