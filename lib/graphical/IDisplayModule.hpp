/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <array>
#include "KeyPressed.hpp"

namespace arcade
{
    class IDisplayModule
    {
        public:
            IDisplayModule() = default;
            ~IDisplayModule() = default;

            virtual void init() = 0;
            virtual void stop() = 0;
            virtual bool game() = 0;
            virtual void textDisplay(const std::string displayText, int xPos, int yPos) = 0;
            virtual void displayMap(std::array<std::string, 19> map) = 0;
            virtual arcade::KeyPressed getKey() = 0;
            virtual void setKey(arcade::KeyPressed newValue) = 0;
    };
}

#endif /* !IDISPLAYMODULE_HPP_ */