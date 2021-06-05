//
// Created by rprec on 05.06.2021.
//

#ifndef CPP_MYCLOCK_H
#define CPP_MYCLOCK_H

#include "SFML/Graphics.hpp"

namespace sf {
    class MyClock {
    private:
        sf::Clock clock;
        float runTime;
        bool bPaused;
    public:
        MyClock();

        void reset();

        void start();

        void pause();

        float getElapsedSeconds();
    };
}

#endif //CPP_MYCLOCK_H
