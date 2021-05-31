//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_STATE_PLAYING_H
#define CPP_STATE_PLAYING_H

#include "SFML/Graphics.hpp"
#include "game_state.h"
#include "console.h"
#include "Resources.h"
#include "labirynth.h"
#include "PacMan.h"
#include "All_ghosts.h"

class State_playing : public Game_state{
private:
    Console* console{};
    Resources resources;
    Labirynth* labirynth{};
    PacMan* pacMan{};

    All_ghosts* ghosts {};




public:
    explicit State_playing(sf::RenderWindow& window) : Game_state(window) {}

    void init();

    void loop() override;

    void render() override;

    void keyPressed(int code) override;

    void keyReleased(int code) override;

    void move_creature(Moving *creature);
};

#endif //CPP_STATE_PLAYING_H
