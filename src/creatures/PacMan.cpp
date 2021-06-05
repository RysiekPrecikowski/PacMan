//
// Created by rprec on 30.05.2021.
//

#include "PacMan.h"

PacMan::PacMan(sf::RenderWindow &window, Maze *maze) : Moving(*maze->starting_positions[pac_man],
                                                              window, maze) {
    console = new Console("PAC MAN");
    setStartingDelay(0.1);
}

void PacMan::eat_food() {
    if (maze->tiles[tile_position.x][tile_position.y]->point == point) {
        eaten_food += 1;
        maze->tiles[tile_position.x][tile_position.y]->point = no_point;
        maze->food_in_maze -= 1;
        points += 10;
    }

    if (maze->tiles[tile_position.x][tile_position.y]->point == big_point) {
        eaten_food += 1;
        maze->tiles[tile_position.x][tile_position.y]->point = no_point;
        maze->food_in_maze -= 1;
        points += 100;
    }

}

int PacMan::get_food_eaten() const {
    return eaten_food;
}



