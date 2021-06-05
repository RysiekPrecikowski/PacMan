//
// Created by rprec on 31.05.2021.
//

#include "Ghost.h"

Ghost::Ghost(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Maze *maze) : Moving(tilePosition, window,
                                                                                              maze) {
    get_directions()->push(left);


}

void Ghost::next_move(sf::Vector2i pos) {
    bool ret = true;
    if (maze->is_crossing(tile_position)) {
        ret = false;
    }

    if (!can_move(get_directions()->front()))
        ret = false;

    if (ret)
        return;

    if (is_frightened) {
        next_move_frightened();
    } else {
        switch (mode) {
            case chase:
                next_move_chase(pos);
                break;
            case scatter:
                next_move_scatter(pos);
                break;

        }
    }
}

int pow2(int val) {
    return val * val;
}

int Ghost::get_distance(int x, int y, sf::Vector2i pos) {
    return pow2(x - pos.x) + pow2(y - pos.y);
}

Directions Ghost::get_best_direction(sf::Vector2i pos) {
    Directions best = right;
    if (!maze->is_crossing(tile_position)) {
        if (can_move(up) and up != -get_directions()->front()) {
            best = up;
        } else if (can_move(left) and left != -get_directions()->front()) {
            best = left;
        } else if (can_move(right) and right != -get_directions()->front()) {
            best = right;
        } else if (can_move(down) and down != -get_directions()->front()) {
            best = down;
        }
        return best;
    }

    if (getGoesThroughFake() and !escaped) {
        console->write("ESCAPE");
        pos.y = 0;
        escaped = true;
    }

    int best_distance = INT_MAX, distance;

    int x = tile_position.x, y = tile_position.y;

    if ((distance = get_distance(x, y - 1, pos)) < best_distance and can_move(up) and
        up != -get_directions()->front()) {
        best_distance = distance;
        best = up;
    }

    if ((distance = get_distance(x - 1, y, pos)) < best_distance and can_move(left) and
        left != -get_directions()->front()) {
        best_distance = distance;
        best = left;
    }
    if ((distance = get_distance(x, y + 1, pos)) < best_distance and can_move(down) and
        down != -get_directions()->front()) {
        best_distance = distance;
        best = down;
    }
    if (get_distance(x + 1, y, pos) < best_distance and can_move(right) and right != -get_directions()->front()) {
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

    target = scatter_mode_target;

    change_direction(direction);
}

void Ghost::next_move_frightened() {
    auto direction = static_cast<Directions>(rand() % 5 - 2);

    while (!can_move(direction) or direction == -get_directions()->front()) {
        direction = static_cast<Directions>(rand() % 5 - 2);
    }

    change_direction(direction);
}

void Ghost::inverse_direction() {
    auto direction = static_cast<Directions>(-get_directions()->front());

    if (can_move(direction)) {
        change_direction(direction);
    } else {
        if (direction == up or direction == down) {
            if (can_move(left))
                change_direction(left);
            else if (can_move(right))
                change_direction(right);

        } else if (direction == left or right) {
            if (can_move(up))
                change_direction(up);
            else if (can_move(down))
                change_direction(down);
        }
    }
}

void Ghost::change_mode(Mode to_mode) {
    mode = to_mode;

    if (chase_counter == 2) {
        base_scatter_duration = 5;
        scale_mode_time();
    } else if (chase_counter == 4) {
        base_chase_duration = 10000000;
        base_scatter_duration = 0;
        scale_mode_time();
    }

    inverse_direction();
}

void Ghost::actualize_mode() {
    if (time_to_change_mode()) {
        switch (mode) {
            case chase:
                change_mode(scatter);
                break;
            case scatter:
                change_mode(chase);
                chase_counter++;
                break;
        }
    }
}

bool Ghost::time_to_change_mode() {
    if (is_frightened) {
        if (frightened_clock.getElapsedSeconds() > frightened_duration) {
            end_frightened();
        } else {
            return false;
        }
    }


    float time = mode_myClock.getElapsedSeconds();

    float delay;

    switch (mode) {
        case chase:
            delay = chase_duration;
            break;
        case scatter:
            delay = scatter_duration;
            break;
    }

    if (time > delay) {
        mode_myClock.reset();

        return true;
    }
    return false;
}

void Ghost::pause() {
    Moving::pause();

    mode_myClock.pause();
    frightened_clock.pause();
}

void Ghost::end_frightened() {
    is_frightened = false;
    scaleDelay(1);
    console->write("END FRIGTHENED");
    mode_myClock.start();
}

void Ghost::scale_mode_time() {
    scatter_duration = mode_duration_scale * base_scatter_duration;
    chase_duration = mode_duration_scale * base_chase_duration;
}
