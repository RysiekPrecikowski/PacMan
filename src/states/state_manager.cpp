//
// Created by rprec on 30.05.2021.
//

#include "state_manager.h"


void State_manager::addState(Game_state* state)
{
    states.push(state);
    states.top()->init();
}

void State_manager::loop()
{
    states.top()->loop();
}

void State_manager::render()
{
    states.top()->render();
}

void State_manager::keyPressed(int code)
{
    states.top()->keyPressed(code);
}

void State_manager::keyReleased(int code)
{
    states.top()->keyReleased(code);
}

State_manager::State_manager(sf::RenderWindow &window) : console("State Manager") {
    this->window = &window;
}
