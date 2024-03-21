/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** lib_sfml
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <string>
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include "../IDisplayModule.hpp"

#define BASE_X 30
#define BASE_Y 60

class lib_sfml : virtual public arcade::IDisplayModule{
    public:
        lib_sfml();
        ~lib_sfml() {};
        void init() override;
        void stop() override;
        bool game() override;
        void textDisplay(const std::string displayText, int xPos, int yPos) override;
        void displayMap(std::array<std::string, 19> map) override;
        arcade::KeyPressed getKey() override;
        void setKey(arcade::KeyPressed newValue) override {};
    private:
        sf::RenderWindow window;
        float x;
        float y;
        float square_size;
        sf::Event event;
        bool key_pressed;
        sf::Font _font;

        sf::Color check_two_char(std::size_t j, std::string str);
        sf::Vector2f get_position(float x, float y);
        sf::Color RGB(int r, int g, int b);
};

extern "C" {
    arcade::IDisplayModule *entrypoint() {
        return (new lib_sfml);
    }
}

#endif /* !SFML_HPP_ */
