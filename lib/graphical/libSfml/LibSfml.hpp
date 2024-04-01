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
    #include "../../includes/IDisplayModule.hpp"

static const int BASE_X = 30;
static const int BASE_Y = 60;

static const std::string FONT_PATH = "lib/graphical/font/ARCADE_N.TTF";
static const std::string WINDOW_TITLE = "Arcade SFML";

namespace arcade
{
    class libSfml : virtual public arcade::IDisplayModule{
        public:
            libSfml();
            ~libSfml() {};
            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() override;
            void game(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override {};
            void changeColor(const std::unordered_map<std::string, Color> patternMap) override {};
            std::string getPlayerName() const override;
        private:
            sf::RenderWindow window;
            float x;
            float y;
            float squareSize;
            sf::Event event;
            sf::Font _font;
            std::map<std::string, sf::RectangleShape> charMap;
            std::string _gameName;
            std::string _playerName;
            arcade::KeyPressed _keyClose;

            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            sf::RectangleShape madeRectangle(sf::Color color, float size);
            bool displayRoundShape(sf::RectangleShape rect, char c);
            void checkTwoChar(std::size_t j, std::string str);
            sf::Vector2f getPosition(float x, float y);
            sf::Color RGB(int r, int g, int b);
    };
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new arcade::libSfml);
    }
}

#endif /* !SFML_HPP_ */
