//
// Created by rprec on 30.05.2021.
//

#include "PacMan.h"

PacMan::PacMan(sf::RenderWindow &window, Labirynth *labirynth) : Moving(*labirynth->starting_positions[pac_man], window, labirynth) {
    console = new Console("PAC MAN");
    setStartingDelay(0.1);
}

void PacMan::eat_food() {
    if(labirynth->tiles[tile_position.x][tile_position.y]->point == point){
        eaten_food += 1;
        labirynth->tiles[tile_position.x][tile_position.y]->point = no_point;
        labirynth->food_in_maze -= 1;
    }
}



int PacMan::get_food_eaten() {
    return eaten_food;
}



