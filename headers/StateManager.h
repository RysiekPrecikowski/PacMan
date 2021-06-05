
#ifndef CPP_STATEMANAGER_H
#define CPP_STATEMANAGER_H

#include <stack>
#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "Console.h"

class State_manager {
private:
    std::stack<Game_state *> states;
    Console console;
    sf::RenderWindow *window;
public:
    explicit State_manager(sf::RenderWindow &window);

    void addState(Game_state *state);

    void loop();

    void render();

    void keyPressed(int code);

    void keyReleased(int code);
};

#endif //CPP_STATEMANAGER_H
