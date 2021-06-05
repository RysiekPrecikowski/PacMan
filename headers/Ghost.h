//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_GHOST_H
#define CPP_GHOST_H

#include "Entity.h"
#include "Moving.h"
#include "Console.h"
#include "PacMan.h"
#include "MyClock.h"

enum Mode {
    chase,
    scatter,
};

class Ghost : public Moving {
private:
    float base_scatter_duration = 7;
    float base_chase_duration = 20;
    float scatter_duration = base_scatter_duration;
    float chase_duration = base_chase_duration;
    int chase_counter = 0;
    float mode_duration_scale = 1;

    void next_move_chase(sf::Vector2i pos);

    void next_move_scatter(sf::Vector2i pos);

    void next_move_frightened();

    void inverse_direction();

    Directions get_best_direction(sf::Vector2i pos);

public:
    bool is_frightened = false;
    bool escaped = false;

    sf::MyClock frightened_clock;
    sf::MyClock mode_myClock;
    float frightened_duration = 15;
    float frightened_speed_ratio = 0.7;

    Ghost(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Maze *maze);

    Console *console;

    sf::Vector2i target;
    sf::Vector2i scatter_mode_target;
    Mode mode = scatter;

    void next_move(sf::Vector2i pos);

    static int get_distance(int x, int y, sf::Vector2i pos);

    void end_frightened();

    bool time_to_change_mode();

    void scale_mode_time();

    void actualize_mode();

    void change_mode(Mode to_mode);

    void pause();
};


#endif //CPP_GHOST_H
