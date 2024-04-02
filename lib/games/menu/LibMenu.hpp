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
            std::array<std::string, 23> getMap() const override;
            std::size_t getMapCellSize() const override;
            std::unordered_map<std::string, Color> getPattern() const override;
            std::vector<std::pair<std::string, std::pair<int, int>>> getText() const override;
            void incrementTime() override {};
            GameStatus updateMap(arcade::KeyPressed key) override;
            std::pair<std::size_t, std::size_t> getIndexes() const override;
            void initText(const std::vector<std::string>, const std::vector<std::string>) override;
        private:
            std::vector<std::string> _gameLibName;
            std::vector<std::string> _graphicalName;
            std::array<std::string, 23> map;
            std::size_t _SelectedGameIndex;
            std::size_t _SelectedLibIndex;
            int _libTypeSelected;
            arcade::KeyPressed oldKeyPressed;

            int changeLibIndex(int index, int change, std::size_t nbLib);
    };
}

extern "C" {
    arcade::IGameModule *entryPoint() {
        return (new arcade::LibMenu);
    }
}

#endif /* !LIBMENU_HPP_ */
