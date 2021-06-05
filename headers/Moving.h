//
// Created by rprec on 31.05.2021.
//

#ifndef CPP_MOVING_H
#define CPP_MOVING_H

#include <queue>
#include "Entity.h"
#include "Directions.h"
#include "Console.h"
#include "Maze.h"

#include "MyClock.h"

class Moving : public Entity {
private:
    sf::MyClock myClock;
    std::queue<Directions> *directions;

    bool alive = true;
    bool goes_through_fake = false;

    bool check_direction(Directions direction);

    bool can_step(int x, int y);

protected:
    float delay = 0.2;
    float starting_delay = 0.2;
    Maze *maze;
    bool paused = false;

public:
    void set_goes_through_fake(bool goesThroughFake);


    Moving(const sf::Vector2i &tilePosition, sf::RenderWindow &window, Maze *maze);

    void move();

    bool can_move(Directions direction);

    void change_direction(Directions direction);

    void enqueueDirection(Directions direction);

    bool time_to_move();

    [[nodiscard]] std::queue<Directions> *get_directions() const;

    void stop();


    void setDelay(float delay);

    void setStartingDelay(float startingDelay);

    void scaleDelay(float ratio);

    [[nodiscard]] float getDelay() const;

    void pause();

    void resume();


    void set_alive(bool state);

    bool is_dead();


    [[nodiscard]] bool getGoesThroughFake() const;
};


#endif //CPP_MOVING_H
