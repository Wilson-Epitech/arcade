/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibSfml
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <string>
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include "../../IDisplayModule.hpp"

static const int BASE_X = 30;
static const int BASE_Y = 60;

static const std::string FONT_PATH = "lib/graphical/font/ARCADE_N.TTF";
static const std::string WINDOW_TITLE = "Arcade SFML";

class libSfml : virtual public arcade::IDisplayModule{
    public:
        libSfml();
        ~libSfml() {};
        void init() override;
        void stop() override;
        bool game() override;
        void displayText(std::vector<std::string> textToDisplay) override;
        void displayMap(std::array<std::string, 21> map, std::size_t size) override;
        arcade::KeyPressed getKey() override;
        void setKey(arcade::KeyPressed newValue) override {};
    private:
        sf::RenderWindow window;
        float x;
        float y;
        float squareSize;
        sf::Event event;
        bool keyPressed;
        sf::Font _font;

        void checkTwoChar(std::size_t j, std::string str);
        sf::Vector2f getPosition(float x, float y);
        sf::Color RGB(int r, int g, int b);
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new libSfml);
    }
}

#endif /* !SFML_HPP_ */
