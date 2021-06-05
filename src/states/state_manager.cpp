//
// Created by rprec on 30.05.2021.
//

#include "state_manager.h"


void State_manager::addState(Game_state* state)
{
    states.push(state);
    states.top()->init();
}

void State_manager::loop() {
    if (states.empty())
        return;

    Game_state::state loop_state = states.top()->loop();
    if (loop_state != Game_state::running) {
        states.pop();
    }

    if (loop_state == Game_state::win){
//        addState()
    }
}

void State_manager::render() {
    if (states.empty())
        return;
    states.top()->render();
}

void State_manager::keyPressed(int code) {
    if (states.empty())
        return;
    states.top()->keyPressed(code);
}

void State_manager::keyReleased(int code) {
    if (states.empty())
        return;
    states.top()->keyReleased(code);
}

State_manager::State_manager(sf::RenderWindow &window) : console("State Manager") {
    this->window = &window;
}
