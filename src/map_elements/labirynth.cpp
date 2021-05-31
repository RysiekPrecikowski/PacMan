//
// Created by rprec on 30.05.2021.
//

#include <fstream>
#include <iostream>
#include "labirynth.h"

using namespace std;
int l[Labirynth::size_x][Labirynth::size_y];

void read_from_file(){
    ifstream fp("maze");
    if (! fp) {
        cout << "Error, file couldn't be opened" << endl;
        return;
    }
    for(int i = 0; i < Labirynth::size_y; i++) {
        for (int j = 0; j < Labirynth::size_x; j++) {
            fp >> l[i][j];
        }
    }
    fp.close();

}




Labirynth::Labirynth(sf::RenderWindow &window){
    this->window = &window;
    for (int i = 0 ; i < size_x ; i ++){
        for(int j = 0 ; j < size_y ; j++){
            tiles[i][j] = new Tile(sf::Vector2i(i, j), window);

            tiles[i][j]->center = false;
            tiles[i][j]->teleport(tiles[i][j]->tile_position);
        }

    }
    read_from_file();
    for (int i = 0 ; i < size_x ; i++){
        for (int j = 0 ; j < size_y ; j++){
            tiles_type type;
            switch (l[j][i]) {
                case 1:
                    type = block;
                    break;
                case 0:
                    type = regular;
                    tiles[i][j]->point = point;
                    food_in_maze += 1;
                    break;
                case 2:
                    type = crossing;
                    break;
                case 3:
                    type = fake_block;
                    break;
                case 4:
                    type = none;
                    break;
            }

            tiles[i][j]->type = type;
        }
    }

    starting_food_in_maze = food_in_maze;

}

bool Labirynth::is_maze(int x, int y) {
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;
//    if (x < 0 or x >= Labirynth::size_x or y < 0 or y >= Labirynth::size_y)
//        return true;

    return tiles[x][y]->type == tiles_type::block;
}

bool Labirynth::is_fake(int x, int y) {
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;
//    if (x < 0 or x >= Labirynth::size_x or y < 0 or y >= Labirynth::size_y)
//        return true;

    return tiles[x][y]->type == tiles_type::fake_block;
}


bool Labirynth::is_crossing(sf::Vector2i position){
    int x = position.x, y = position.y;
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;
    if (
            x < 0 or
            x >= Labirynth::size_x or
            y < 0 or
            y >= Labirynth::size_y)
        return true;

    return tiles[x][y]->type == crossing;
}

Tile::Tile(const sf::Vector2i &tilePosition, sf::RenderWindow& window) : Entity(tilePosition, window) {}
