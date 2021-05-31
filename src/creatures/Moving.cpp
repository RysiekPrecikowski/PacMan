//
// Created by rprec on 31.05.2021.
//

#include "Moving.h"

Moving::Moving(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Labirynth *labirynth) : Entity(tilePosition, window) {
    directions = new std::queue<Directions>;
    this->labirynth = labirynth;
}

void Moving::move() {
//    float diff = move_diff;

    if (!directions->empty()) {
        Directions direction = directions->front();
//        directions->pop();
        sf::Vector2i pos(tile_position);
        switch (direction) {
            case up:
//                Entity::move(0, -diff);
                pos.y += -1;
                break;
            case down:
                pos.y += 1;
//                Entity::move(0, diff);
                break;
            case left:
                pos.x += -1;
//                Entity::move(-diff, 0);
                break;
            case right:
                pos.x += 1;
//                Entity::move(diff, 0);
                break;
        }

        teleport(pos);
    }
}

void Moving::stop() {
    if(not directions->empty())
        directions->pop();
}

#include <iostream>

bool Moving::check_direction(Directions direction){
    if (directions->empty()) {
        return true;
    }

    if (!can_move(direction) ){
        return true;
    }

    if(direction != directions->front())
        return true;

//    std::cout<<"RETURN CHECK DIRECTION";
    return false;
}

void Moving::enqueueDirection(Directions direction) {
    if (check_direction(direction) == false)
        return;

    if (not directions->empty()) {
        if (direction == -directions->front()) {
            auto *empty = new std::queue<Directions>;
            std::swap(directions, empty);
        } else if (directions->size() == 2) {
//            auto *q = new std::queue<Directions>;
//            q->push(directions->back());
//            std::swap(directions, q);
        }
    }

//    if (directions->empty())
    if (directions->size() < 2)
        directions->push(direction);
//    else {
//        if (directions->front() != direction){
//            directions->push(direction);
//        }
//    }

}

void Moving::change_direction(Directions direction) {
    auto *q = new std::queue<Directions>;
    std::swap(directions, q);
    directions->push(direction);
}

std::queue<Directions> *Moving::get_directions() const {
    return directions;
}

void Moving::set_alive(bool state) {
    alive = state;
}

bool Moving::is_dead() {
    return not alive;
}




//bool in_tile(float x, float y, Tile *tile){
//    return (
//            x > tile->screen_position.x and x < tile->screen_position.x + tile->get_tile_dimensions().x and
//            y > tile->screen_position.y and y < tile->screen_position.y + tile->get_tile_dimensions().y);
//}
//
//bool is_maze(Moving *creature, Directions direction) {
//    float x = creature->screen_position.x, y = creature->screen_position.y;
//
//    float offset_x=0, offset_y=0;
//
//    if(direction == right){
//        offset_x = creature->move_diff;
//        x += creature->move_diff;
//    }
//    if (direction == left){
//        x -= creature->move_diff;
//    }
//    if (direction == up){
//        y -= creature->move_diff;
//    }
//    if (direction == down){
//        y += creature->move_diff;
//        offset_y += creature->move_diff;
//    }
//
//
//    if (
//            x < 0 or
//            x >= creature->window->getSize().x or
//            y < 0 or
//            y >= creature->window->getSize().y)
//        return true;
//
//    if(creature->tile_position.x < 0 or creature->tile_position.y >= creature->labirynth->size_x)
//        return true;
//
//    for (int i = 0 ; i < 3 ; i ++){
//        for(int j = 0 ; j < 3 ; i++){
//            if (in_tile(x + offset_x, y + offset_y, creature->labirynth->tiles[creature->tile_position.x][creature->tile_position.y]))
//                return true;
//        }
//    }
//    return false;
//}


bool Moving::can_step(int x, int y){
    if (goes_through_fake)
        return !labirynth->is_maze(x, y);
    else
        return !labirynth->is_maze(x, y) and !labirynth->is_fake(x, y);
}

bool Moving::can_move(Directions direction){
    if (direction == Directions::NONE){
        return false;
    }

//    return !is_maze(this, direction);

    switch (direction) {
        case up:
            return can_step(tile_position.x, tile_position.y-1);
        case down:
            return can_step(tile_position.x, tile_position.y+1);
        case left:
            return can_step(tile_position.x - 1, tile_position.y);
        case right:
            return can_step(tile_position.x + 1, tile_position.y);
    }
    return true;
}

void Moving::setGoesThroughFake(bool goesThroughFake) {
    goes_through_fake = goesThroughFake;
}

void Moving::setDelay(float delay) {
    Moving::delay = delay;
}

void Moving::setStartingDelay(float startingDelay) {
    starting_delay = startingDelay;
    delay = startingDelay;
}

void Moving::scaleDelay(float ratio) {
    delay = ratio * starting_delay;
}

float Moving::getDelay() const {
    return delay;
}
