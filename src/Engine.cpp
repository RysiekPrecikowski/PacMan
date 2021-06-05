//
// Created by rprec on 30.05.2021.
//

#include "Engine.h"


Engine::Engine() : console("Engine") {
    window = new RenderWindow(VideoMode(500, 642), "Pac Man");
    game_states = new State_manager(*window);
    console.write("Window created");

    game_states->addState(new State_playing(*window));
}

bool Engine::is_running() {
    return window->isOpen();
}

void Engine::handle_events() {
    Event event;

    while (window->pollEvent(event)) {

        switch (event.type) {
            case sf::Event::Closed:
                console.write("Closing window");
                window->close();
                break;
            case Event::KeyPressed:
                game_states->keyPressed(event.key.code);
                break;
            case Event::KeyReleased:
                game_states->keyReleased(event.key.code);
                break;
        }
    }

    game_states->loop();
//    }
}

void Engine::render() {
    window->clear(Color::Black);
    game_states->render();
    window->display();
}
