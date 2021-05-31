
#ifndef CPP_STATE_MANAGER_H
#define CPP_STATE_MANAGER_H

#include <stack>
#include "SFML/Graphics.hpp"
#include "game_state.h"
#include "console.h"

class State_manager
{
private:
    std::stack<Game_state*> states;
    Console console;
    sf::RenderWindow* window;
public:
    explicit State_manager(sf::RenderWindow& window);

    void addState(Game_state* state);
    void loop();
    void render();
    void keyPressed(int code);
    void keyReleased(int code);
};

#endif //CPP_STATE_MANAGER_H
