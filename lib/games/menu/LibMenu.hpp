/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** LibMenu
*/

#ifndef LIBMENU_HPP_
#define LIBMENU_HPP_

#include "../../includes/IGameModule.hpp"
#include "../../includes/Color.hpp"
#include "../../includes/KeyPressed.hpp"
#include "../../includes/GameStatus.hpp"
#include <string>
#include <iostream>
#include <chrono>

namespace arcade {
    class LibMenu : virtual public arcade::IGameModule {
        public:
            LibMenu();
            ~LibMenu() {};
            void resetGame() override;
            std::array<std::string, 23> getMap() override;
            std::map<std::string, Color> getPattern() override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() override;
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::size_t getMapCellSize() override;
            void initText(std::vector<std::string>, std::vector<std::string>) override;
            std::pair<std::size_t, std::size_t> getIndexes() override {};
        private:
            std::vector<std::string> _gameLibName;
            std::vector<std::string> _graphicalName;

    };
}


#endif /* !LIBMENU_HPP_ */
