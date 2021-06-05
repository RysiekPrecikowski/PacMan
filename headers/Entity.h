//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_ENTITY_H
#define CPP_ENTITY_H

#include "SFML/Graphics.hpp"

class Entity {
private:

public:
    sf::RenderWindow* window;
    sf::Vector2f screen_position;
    sf::Vector2i tile_position;

    sf::Vector2f tile_dimensions = sf::Vector2f (-1, -1);

    explicit Entity(const sf::Vector2i &tilePosition, sf::RenderWindow &window);

    void move(sf::Vector2f vector);
    void teleport(sf::Vector2i tile);

    void move(float diff_x, float diff_y);
    void teleport(int x, int y);

    sf::Vector2f get_tile_dimensions();
};


#endif //CPP_ENTITY_H
