//
// Created by rprec on 31.05.2021.
//

#include "Moving.h"

Moving::Moving(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Maze *labirynth) : Entity(tilePosition, window) {
    directions = new std::queue<Directions>;
    this->maze = labirynth;
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
        }
    }

    if (directions->size() < 2)
        directions->push(direction);
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

bool Moving::can_step(int x, int y){
    if (goes_through_fake)
        return !maze->is_maze(x, y);
    else
        return !maze->is_maze(x, y) and !maze->is_fake(x, y);
}

bool Moving::can_move(Directions direction){
    if (direction == Directions::NONE){
        return false;
    }


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

bool Moving::getGoesThroughFake() const {
    return goes_through_fake;
}

void Moving::pause() {
    myClock.pause();
    paused = true;
}

void Moving::resume() {
    myClock.start();
    paused= false;
}

bool Moving::time_to_move() {
    float time = myClock.getElapsedSeconds();

    if (time > delay){
        myClock.reset();
        return true;
    }

    return false;
}
