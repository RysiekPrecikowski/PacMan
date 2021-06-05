//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_GAMESTATE_H
#define CPP_GAMESTATE_H

#include "SFML/Graphics.hpp"

class Game_state {

protected:
    sf::RenderWindow *window;

public:
    enum state {
        running,
        ended,
        win
    };

    explicit Game_state(sf::RenderWindow &window) : window(&window) {}

    virtual void init() {};

    virtual state loop() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual void render() = 0;

    virtual void key_pressed(int code) = 0;

    virtual void key_released(int code) = 0;

    bool paused = false;
};

#endif //CPP_GAMESTATE_H
