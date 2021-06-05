//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_PACMAN_H
#define CPP_PACMAN_H

#include "Entity.h"
#include "Moving.h"
#include "Directions.h"
#include "console.h"
#include <queue>

class PacMan : public Moving {
private:
    int eaten_food = 0;
    Console *console;

public:
    int points=0;
    PacMan(sf::RenderWindow &window, Maze *maze);

    void eat_food();
    int get_food_eaten() const;
};



#endif //CPP_PACMAN_H
