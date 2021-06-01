//
// Created by rprec on 31.05.2021.
//

#include "Ghost.h"

Ghost::Ghost(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Labirynth *labirynth) : Moving(tilePosition, window, labirynth) {
    get_directions()->push(left);


}

void Ghost::next_move(sf::Vector2i pos) {
    bool ret = true;
    if (labirynth->is_crossing(tile_position)) {
        ret = false;
    }

    if (!can_move(get_directions()->front()))
        ret = false;

    if (ret)
        return;

    switch (mode) {
        case chase:
            next_move_chase(pos);
            break;
        case scatter:
            next_move_scatter(pos);
            break;

    }
}

int pow2(int val){
    return val * val;
}

int Ghost::get_distance(int x, int y, sf::Vector2i pos){
    return pow2(x - pos.x) + pow2(y - pos.y);
}

Directions Ghost::get_best_direction(sf::Vector2i pos){
    Directions best = right;
    if (!labirynth->is_crossing(tile_position)){
        if(can_move(up) and up != -get_directions()->front()){
            best = up;
        } else if (can_move(left) and left != -get_directions()->front()) {
            best = left;
        } else if (can_move(right) and right != -get_directions()->front()){
            best = right;
        } else if (can_move(down) and down != -get_directions()->front()){
            best = down;
        }
        return best;
    }


    int best_distance = INT_MAX, distance;

    int x = tile_position.x, y = tile_position.y;

    if ((distance = get_distance(x , y -1, pos)) < best_distance and can_move(up) and up != -get_directions()->front()){
        best_distance = distance;
        best = up;
    }

    if ((distance = get_distance(x -1 , y, pos)) < best_distance and can_move(left) and left != -get_directions()->front()){
        best_distance = distance;
        best = left;
    }
    if ((distance = get_distance(x , y + 1, pos)) < best_distance and can_move(down) and down != -get_directions()->front()){
        best_distance = distance;
        best = down;
    }
    if ((distance = get_distance(x + 1 , y, pos)) < best_distance and can_move(right) and right != -get_directions()->front()){
        best_distance = distance;
        best = right;
    }

    return best;
}

void Ghost::next_move_chase(sf::Vector2i pos) {
    Directions direction = get_best_direction(pos);

    target = pos;

    change_direction(direction);
}

void Ghost::next_move_scatter(sf::Vector2i pos) {
    Directions direction = get_best_direction(scatter_mode_target);

    target = pos;

    change_direction(direction);
}

void Ghost::inverse_direction(){
    auto direction = static_cast<Directions>(-get_directions()->front());

    std::string message = "CHANGE DIRECTION from " + std::to_string(get_directions()->front()) + " to ";
    if (can_move(direction)){
        change_direction(direction);
    } else {
        if (direction == up or direction == down) {
            if (can_move(left))
                change_direction(left);
            else if (can_move(right))
                change_direction(right);

        } else if (direction == left or right){
            if (can_move(up))
                change_direction(up);
            else if (can_move(down))
                change_direction(down);
        }
    }
    message += std::to_string(get_directions()->front());

    console->write(message);
}

void Ghost::change_mode(Mode to_mode){
    mode = to_mode;

    if(chase_counter == 2){
        base_scatter_duration = 5;
        scale_mode_time();
    } else if (chase_counter == 4){
        base_chase_duration = 10000000;
        base_scatter_duration = 0;
        scale_mode_time();
    }


    console->write("CHANGE MODE " + std::to_string(to_mode));

    inverse_direction();
}

void Ghost::actualize_mode() {
    if (time_to_change_mode()){
        switch (mode) {
            case chase:
                change_mode(scatter);
                break;
            case scatter:
                change_mode(chase);
                chase_counter ++;
                break;
        }
    }
}
