//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_ALL_GHOSTS_H
#define CPP_ALL_GHOSTS_H

#include "SFML/Graphics.hpp"
#include "Ghost.h"
#include "Resources.h"
#include "PacMan.h"

class All_ghosts {
    Maze *maze;
public:
    std::map<Ghosts, Ghost*> ghosts {};

    All_ghosts(sf::RenderWindow &window, Maze *maze);

    void move_ghosts(PacMan *PacMan);

    void frighten_ghosts();
};


#endif //CPP_ALL_GHOSTS_H
