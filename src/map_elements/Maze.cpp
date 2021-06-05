//
// Created by rprec on 30.05.2021.
//

#include <fstream>
#include <iostream>
#include "Maze.h"

using namespace std;
int l[Maze::size_x][Maze::size_y];

void read_from_file() {
    ifstream fp("maze");
    if (!fp) {
        cout << "Error, file couldn't be opened" << endl;
        return;
    }
    for (int i = 0; i < Maze::size_y; i++) {
        for (int j = 0; j < Maze::size_x; j++) {
            fp >> l[i][j];
        }
    }
    fp.close();

}

Maze::Maze(sf::RenderWindow &window) {
    this->window = &window;
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
            tiles[i][j] = new Tile(sf::Vector2i(i, j), window);

            tiles[i][j]->teleport(tiles[i][j]->tile_position);
        }
    }

    read_from_file();
    for (int i = 0; i < size_x; i++) {
        for (int j = 0; j < size_y; j++) {
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
                    tiles[i][j]->point = point;
                    food_in_maze += 1;
                    break;
                case 3:
                    type = fake_block;
                    break;
                case 4:
                    type = none;
                    break;
                case 5:
                    starting_positions[pac_man] = new sf::Vector2i(i, j);
                    type = regular;
                    break;
                case 6:
                    starting_positions[inky] = new sf::Vector2i(i, j);
                    type = regular;
                    break;
                case 7:
                    starting_positions[blinky] = new sf::Vector2i(i, j);
                    type = regular;
                    tiles[i][j]->point = point;
                    food_in_maze += 1;
                    break;
                case 8:
                    starting_positions[clyde] = new sf::Vector2i(i, j);
                    type = regular;
                    break;
                case 9:
                    starting_positions[pinky] = new sf::Vector2i(i, j);
                    type = regular;
                    break;
                case 10:
                    type = regular;
                    tiles[i][j]->point = big_point;
                    food_in_maze += 1;
                    break;
                case 11:
                    type = crossing;
                    break;
            }

            tiles[i][j]->type = type;
        }
    }

    starting_food_in_maze = food_in_maze;
}

bool Maze::is_maze(int x, int y) {
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;

    return tiles[x][y]->type == tiles_type::block;
}

bool Maze::is_fake(int x, int y) {
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;

    return tiles[x][y]->type == tiles_type::fake_block;
}


bool Maze::is_crossing(sf::Vector2i position) {
    int x = position.x, y = position.y;
    x = (x + size_x) % size_x;
    y = (y + size_y) % size_y;

    return tiles[x][y]->type == crossing;
}

Tile::Tile(const sf::Vector2i &tilePosition, sf::RenderWindow &window) : Entity(tilePosition, window) {}
