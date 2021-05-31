//
// Created by rprec on 30.05.2021.
//

#include <cmath>
#include "Entity.h"
#include "labirynth.h"

Entity::Entity(const sf::Vector2i &tilePosition, sf::RenderWindow& window)
: tile_position(tilePosition), window(&window) {
//    screen_position.x = tilePosition.x * 16 + 8 + 8;
//    screen_position.y = tilePosition.y * 16 + 8;
    teleport(tilePosition);

}

void Entity::move(float diff_x, float diff_y){
    move(sf::Vector2f(diff_x, diff_y));
}
#include <iostream>

void Entity::move(sf::Vector2f vector) {
    screen_position += vector;

    auto tile_dimensions = get_tile_dimensions();

    if (vector.x < 0){
        tile_position.x = (int) std::round((screen_position.x + tile_dimensions.x/2  ) / tile_dimensions.x);
    } else if (vector.x > 0) {
        tile_position.x = (int) std::round((screen_position.x - tile_dimensions.x/2  ) / tile_dimensions.x);
    }


    if (vector.y < 0){
        tile_position.y = (int) std::round((screen_position.y + tile_dimensions.y/2 ) / tile_dimensions.y);
    } else if (vector.y > 0) {
        tile_position.y = (int) std::round((screen_position.y - tile_dimensions.y/2 ) / tile_dimensions.y);
    }
}

void Entity::teleport(int x, int y) {
    teleport(sf::Vector2i(x, y));
}

void Entity::teleport(sf::Vector2i tile) {
    tile_position = tile;

    tile_position.x = (Labirynth::size_x + tile_position.x) % Labirynth::size_x;
    tile_position.y = (Labirynth::size_y + tile_position.y) % Labirynth::size_y;

    auto tile_dimensions = get_tile_dimensions();


    screen_position.x = tile_position.x * tile_dimensions.x;
    screen_position.y = tile_position.y * tile_dimensions.y;
}

sf::Vector2f Entity::get_tile_dimensions() {
    float tile_width = window->getSize().x /(float)  Labirynth::size_x;
    float tile_height = window->getSize().y /(float)  Labirynth::size_y;
    return sf::Vector2f (tile_width, tile_height);
}



