//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_RESOURCES_H
#define CPP_RESOURCES_H

#include "SFML/Graphics.hpp"
#include "console.h"

enum Ghosts {
    Blinky,
    Pinky,
    Inky,
    Clyde,
};



class Resources{
private:
    Console console;
public:
    Resources();

    void load();

    sf::Sprite *point;
    sf::Texture point_texture;

    sf::Sprite *PacMan;
    sf::Texture PacMan_texture;

    sf::Sprite *tile;
    sf::Texture tile_texture;

    std::map<Ghosts, sf::Sprite*> ghosts;
    std::map<Ghosts, sf::Texture> ghosts_textures;


    sf::Vector2f get_scale(sf::RenderWindow &window, sf::Texture &texture);
};

#endif //CPP_RESOURCES_H
