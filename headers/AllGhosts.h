//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_ALLGHOSTS_H
#define CPP_ALLGHOSTS_H

#include "SFML/Graphics.hpp"
#include "Ghost.h"
#include "Resources.h"
#include "PacMan.h"

class AllGhosts {
    Maze *maze;
public:
    std::map<Ghosts, Ghost *> ghosts{};

    AllGhosts(sf::RenderWindow &window, Maze *maze);

    void move_ghosts(PacMan *PacMan);

    void frighten_ghosts();
};


#endif //CPP_ALLGHOSTS_H
