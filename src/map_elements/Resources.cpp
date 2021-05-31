//
// Created by rprec on 30.05.2021.
//

#include <Engine.h>
#include "Resources.h"

using namespace sf;



void Resources::load() {
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

    for (auto p : ghosts_textures){
        ghosts[p.first] = new Sprite(ghosts_textures[p.first]);
    }

    console.write("Ghosts loaded");
}


Vector2f Resources::get_scale(RenderWindow &window, Texture& texture){
    float scale_x = ((float) 1 / Labirynth::size_x) * window.getSize().x / texture.getSize().x;
    float scale_y = ((float) 1 / Labirynth::size_y) * window.getSize().y / texture.getSize().y;
    return Vector2f (scale_x, scale_y);
}

Resources::Resources() : console("Resources") {}
