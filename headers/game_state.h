//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_GAME_STATE_H
#define CPP_GAME_STATE_H

#include "SFML/Graphics.hpp"

class Game_state
{

protected:
    sf::RenderWindow* window;


public:


    explicit Game_state(sf::RenderWindow &window) : window(&window) {}

    virtual void init() {};
    virtual void loop() = 0;
    virtual void render() = 0;
    virtual void keyPressed(int code) = 0;
    virtual void keyReleased(int code) = 0;
};

#endif //CPP_GAME_STATE_H
