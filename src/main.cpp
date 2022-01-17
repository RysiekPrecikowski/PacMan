#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#include <ctime>
#include <iostream>

using namespace std;

#include "Engine.h"


int main() {
    srand(time(nullptr));

    Engine engine;

    while (engine.is_running()) {
        engine.handle_events();
        engine.render();

    }

    return 0;
}
#pragma clang diagnostic pop