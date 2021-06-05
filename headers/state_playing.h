//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_STATE_PLAYING_H
#define CPP_STATE_PLAYING_H

#include "SFML/Graphics.hpp"
#include "game_state.h"
#include "console.h"
#include "Resources.h"
#include "Maze.h"
#include "PacMan.h"
#include "All_ghosts.h"

class State_playing : public Game_state{
private:
    Console* console{};
    Resources resources;
    Maze* maze{};
    PacMan* pacMan{};

    All_ghosts* ghosts {};


    bool win= false;
    bool lost = false;

    void check_collisions();
    void move_creature(Moving *creature);
    void reset_positions();

    void render_maze();
    void render_creatures();
    void render_text();

public:
    explicit State_playing(sf::RenderWindow& window) : Game_state(window) {}

    void init() override;

    state loop() override;

    void render() override;

    void keyPressed(int code) override;

    void keyReleased(int code) override;

    void pause() override;

    void resume() override;
};

#endif //CPP_STATE_PLAYING_H
