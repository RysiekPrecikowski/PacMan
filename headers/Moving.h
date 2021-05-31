//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_MOVING_H
#define CPP_MOVING_H

#include <queue>
#include "Entity.h"
#include "Directions.h"
#include "console.h"
#include "labirynth.h"

class Moving : public Entity {
    sf::Clock clock;
    float timer = 0;
protected:
public:
    void setDelay(float delay);

protected:
    float delay = 0.2;
    float starting_delay = 0.2;
public:
    void setStartingDelay(float startingDelay);
    void scaleDelay(float ratio);

private:
    std::queue<Directions>* directions;

    bool alive = true;
    bool goes_through_fake = false;
public:
    void setGoesThroughFake(bool goesThroughFake);

public:
    Labirynth* labirynth;
    float move_diff = 0.5;
    Moving(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Labirynth* labirynth);

    void move();
    void stop();

    void enqueueDirection(Directions direction);

    [[nodiscard]] std::queue<Directions>* get_directions() const;

    void set_alive(bool state);
    bool is_dead();

    bool can_move(Directions direction);

    bool check_direction(Directions direction);

    void change_direction(Directions direction);

    bool can_step(int x, int y);

    bool time_to_move(){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        if (timer > delay){
            timer = 0;
            return true;
        }
        return false;
    }

    float getDelay() const;
};


#endif //CPP_MOVING_H
