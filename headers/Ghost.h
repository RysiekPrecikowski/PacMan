//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_GHOST_H
#define CPP_GHOST_H

#include "Entity.h"
#include "Moving.h"
#include "console.h"
#include "PacMan.h"

enum Mode{
    chase,
    scatter
};

class Ghost : public Moving {



public:
    Ghost(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Labirynth *labirynth);
    Console *console;

    sf::Vector2i target;
    sf::Vector2i scatter_mode_target;
    Mode mode = chase;
    Directions get_best_direction(sf::Vector2i pos);

    void next_move_chase(sf::Vector2i pos);

    void next_move_scatter(sf::Vector2i pos);

    void next_move(sf::Vector2i pos);

    static int get_distance(int x, int y, sf::Vector2i pos);
};


#endif //CPP_GHOST_H
