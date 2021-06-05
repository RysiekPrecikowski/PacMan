//
// Created by rprec on 30.05.2021.
//

#include <cmath>
#include "Entity.h"
#include "Maze.h"

Entity::Entity(const sf::Vector2i &tilePosition, sf::RenderWindow &window)
        : tile_position(tilePosition), window(&window) {
    teleport(tilePosition);
}

void Entity::move(float diff_x, float diff_y) {
    move(sf::Vector2f(diff_x, diff_y));
}

#include <iostream>

void Entity::move(sf::Vector2f vector) {
    screen_position += vector;

    auto tile_dimensions = get_tile_dimensions();

    if (vector.x < 0) {
        tile_position.x = (int) std::round((screen_position.x + tile_dimensions.x / 2) / tile_dimensions.x);
    } else if (vector.x > 0) {
        tile_position.x = (int) std::round((screen_position.x - tile_dimensions.x / 2) / tile_dimensions.x);
    }


    if (vector.y < 0) {
        tile_position.y = (int) std::round((screen_position.y + tile_dimensions.y / 2) / tile_dimensions.y);
    } else if (vector.y > 0) {
        tile_position.y = (int) std::round((screen_position.y - tile_dimensions.y / 2) / tile_dimensions.y);
    }
}

void Entity::teleport(int x, int y) {
    teleport(sf::Vector2i(x, y));
}

void Entity::teleport(sf::Vector2i tile) {
    tile_position = tile;

    tile_position.x = (Maze::size_x + tile_position.x) % Maze::size_x;
    tile_position.y = (Maze::size_y + tile_position.y) % Maze::size_y;

    auto tile_dimensions = get_tile_dimensions();


    screen_position.x = tile_position.x * tile_dimensions.x;
    screen_position.y = tile_position.y * tile_dimensions.y;
}

sf::Vector2f Entity::get_tile_dimensions() {
    if (tile_dimensions.x < 0 and tile_dimensions.y < 0) {
        float tile_width = window->getSize().x / (float) Maze::size_x;
        float tile_height = window->getSize().y / (float) Maze::size_y;
        tile_dimensions.x = tile_width;
        tile_dimensions.y = tile_height;
    }
    return tile_dimensions;
}



