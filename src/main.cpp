#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
#include <iostream>

using namespace std;

#include "Engine.h"


int main(){
    srand(time(nullptr));

    Engine engine;

    while (engine.is_running()){
        engine.handle_events();
        engine.render();

    }

    return 0;
}