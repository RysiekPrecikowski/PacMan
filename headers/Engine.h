//
// Created by rprec on 30.05.2021.
//

#ifndef PACMAN_ENGINE_H
#define PACMAN_ENGINE_H

#include <SFML/Graphics.hpp>
#include "Console.h"

#include "StateManager.h"
#include "StatePlaying.h"

using namespace sf;

class Engine {
private:
    RenderWindow *window = nullptr;
    Console console;
    State_manager *game_states = nullptr;

public:
    Engine();

    bool is_running();

    void handle_events();

    void render();

};


#endif //PACMAN_ENGINE_H
