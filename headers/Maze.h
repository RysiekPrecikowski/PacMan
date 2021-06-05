//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_MAZE_H
#define CPP_MAZE_H

#include "Entity.h"

#include "Directions.h"

enum tiles_type{
    none,
    crossing,
    block,
    fake_block,
    regular,
    all_types
};

enum point_type{
    no_point,
    point,
    big_point
};

enum starting_pos{
    pac_man,
    pinky,
    inky,
    clyde,
    blinky
};

class Tile : public Entity{
public:
    Tile(const sf::Vector2i &tilePosition, sf::RenderWindow& window);

    tiles_type type = tiles_type::none;
    point_type point = point_type::no_point;
};

class Maze {
    sf::RenderWindow *window;
public:
    static const int size_x = 28;
    static const int size_y = 36;

    int food_in_maze = 0;
    int starting_food_in_maze = 0;
    Tile* tiles[size_x][size_y]{};

    explicit Maze(sf::RenderWindow& window);
    bool is_maze(int x, int y);
    bool is_crossing(sf::Vector2i position);
    bool is_fake(int x, int y);

    std::map<starting_pos, sf::Vector2i*> starting_positions;
};


#endif //CPP_MAZE_H
