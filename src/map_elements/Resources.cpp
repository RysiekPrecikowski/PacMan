//
// Created by rprec on 30.05.2021.
//

#include <Engine.h>
#include "Resources.h"

using namespace sf;



void Resources::load(sf::RenderWindow *window) {
    font.loadFromFile("fonts/OpenSans-Regular.ttf");
    console.write("Font loaded");

    frightened_ghost_texture.loadFromFile("images/frightened.png");
    frightened_ghost = new Sprite(frightened_ghost_texture);
    console.write("Frightened ghost loaded");

    big_point_texture.loadFromFile("images/big_point.png");
    big_point = new Sprite(big_point_texture);
    console.write("Big point loaded");

    point_texture.loadFromFile("images/point.png");
    point = new Sprite(point_texture);
    console.write("Point loaded");

    PacMan_texture.loadFromFile("images/PacMan.png");
    PacMan = new Sprite(PacMan_texture);
    console.write("PacMan loaded");

    tile_texture.loadFromFile("images/tile.png");
    tile = new Sprite(tile_texture);
    console.write("Tile loaded");

    ghosts_textures[Blinky].loadFromFile("images/blinky.png");
    ghosts_textures[Clyde].loadFromFile("images/clyde.png");
    ghosts_textures[Inky].loadFromFile("images/inky.png");
    ghosts_textures[Pinky].loadFromFile("images/pinky.png");

    for (const auto& p : ghosts_textures){
        ghosts[p.first] = new Sprite(ghosts_textures[p.first]);
    }
    console.write("Ghosts loaded");

    for (auto p:ghosts){
        p.second->setScale(get_scale(*window, ghosts_textures[p.first]));
    }

    frightened_ghost->setScale(get_scale(*window, frightened_ghost_texture));
    big_point->setScale(get_scale(*window, big_point_texture));
    point->setScale(get_scale(*window, point_texture));
    PacMan->setScale(get_scale(*window, PacMan_texture));
    tile->setScale(get_scale(*window, tile_texture));


    console.write("Scale set");
}


Vector2f Resources::get_scale(RenderWindow &window, Texture& texture){
    float scale_x = ((float) 1 / Maze::size_x) * window.getSize().x / texture.getSize().x;
    float scale_y = ((float) 1 / Maze::size_y) * window.getSize().y / texture.getSize().y;
    return Vector2f (scale_x, scale_y);
}

Resources::Resources() : console("Resources") {}
