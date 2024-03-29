/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** KeyPressed
*/

#ifndef KEYPRESSED_HPP_
#define KEYPRESSED_HPP_

namespace arcade
{
    enum KeyPressed
    {
        OTHER,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        R, // reset
        BACKSPACE, // exit game
        CLOSE_BUTTON,
        P, // previous lib graphic
        N, // next lib graphic
        G, // swith entre les jeux (en boucle)
        ENTER, // alors la c dur de savoir
        M // revenir au menu si on est pas deja dedan
    };
}

#endif /* !KEYPRESSED_HPP_ */