//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_STATEPLAYING_H
#define CPP_STATEPLAYING_H

#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Console.h"
#include "Resources.h"
#include "Maze.h"
#include "PacMan.h"
#include "AllGhosts.h"

class State_playing : public Game_state {
private:
    Console *console{};
    Resources resources;
    Maze *maze{};
    PacMan *pacMan{};

    AllGhosts *ghosts{};


    bool win = false;
    bool lost = false;

    void check_collisions();

    void move_creature(Moving *creature);

    void reset_positions();

    void render_maze();

    void render_creatures();

    void render_text();

public:
    explicit State_playing(sf::RenderWindow &window) : Game_state(window) {}

    void init() override;

    state loop() override;

    void render() override;

    void key_pressed(int code) override;

    void key_released(int code) override;

    void pause() override;

    void resume() override;
};

#endif //CPP_STATEPLAYING_H
