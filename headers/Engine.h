//
// Created by rprec on 30.05.2021.
//

#ifndef PACMAN_ENGINE_H
#define PACMAN_ENGINE_H

#include <SFML/Graphics.hpp>
#include "console.h"

#include "state_manager.h"
#include "state_playing.h"

using namespace sf;

class Engine{
private:
    sf::Clock clock;
    float timer = 0;
    float delay = 0.2;
    RenderWindow* window = nullptr;
    Console console;
    State_manager* game_states = nullptr;

public:
    Engine();

    bool is_running();
    void handle_events();
    void render();

};




#endif //PACMAN_ENGINE_H
