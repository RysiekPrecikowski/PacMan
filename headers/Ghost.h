//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_GHOST_H
#define CPP_GHOST_H

#include "Entity.h"
#include "Moving.h"
#include "console.h"
#include "PacMan.h"

enum Mode{
    chase,
    scatter,
    frightened // TODO
};

class Ghost : public Moving {
    sf::Clock mode_clock;
    float mode_timer = 0;
    float base_scatter_duration = 7;
    float base_chase_duration = 20;
    float scatter_duration = base_scatter_duration;
    float chase_duration = base_chase_duration;
    int chase_counter = 0;
    float mode_duration_scale = 1;

public:
    Ghost(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Labirynth *labirynth);
    Console *console;

    sf::Vector2i target;
    sf::Vector2i scatter_mode_target;
    Mode mode = scatter;
    Directions get_best_direction(sf::Vector2i pos);

    void next_move_chase(sf::Vector2i pos);

    void next_move_scatter(sf::Vector2i pos);

    void next_move(sf::Vector2i pos);

    static int get_distance(int x, int y, sf::Vector2i pos);

    bool time_to_change_mode(){
        float time = mode_clock.getElapsedTime().asSeconds();
        mode_clock.restart();
        mode_timer += time;

        float delay;

        switch (mode) {
            case chase:
                delay = chase_duration;
                break;
            case scatter:
                delay = scatter_duration;
                break;
        }

        if (mode_timer > delay){
            mode_timer = 0;
            return true;
        }
        return false;
    }

    void scale_mode_time(){
        scatter_duration = mode_duration_scale * base_scatter_duration;
        chase_duration = mode_duration_scale * base_chase_duration;
    }

    void actualize_mode();

    void change_mode(Mode to_mode);

    void inverse_direction();
};


#endif //CPP_GHOST_H
