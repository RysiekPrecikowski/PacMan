//
// Created by rprec on 05.06.2021.
//

#include "MyClock.h"

sf::MyClock::MyClock() {
    bPaused = false;
    runTime = 0;
    clock.restart();
}

void sf::MyClock::reset() {
    clock.restart();
    runTime = 0;
    bPaused = false;
}

void sf::MyClock::start() {
    if (bPaused) {
        clock.restart();
    }
    bPaused = false;
}

void sf::MyClock::pause() {
    if (!bPaused) {
        runTime += clock.getElapsedTime().asSeconds();
    }
    bPaused = true;
}

float sf::MyClock::getElapsedSeconds() {
    if (!bPaused) {
        return runTime + clock.getElapsedTime().asSeconds();
    }
    return runTime;
}
