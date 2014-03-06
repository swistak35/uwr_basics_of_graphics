#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "graphics_class.hpp"
#include "observer_class.hpp"

using namespace std;
// dodac kopyrajty

int main(int argc, char *argv[]) {
    GraphicsEngine engine;
    Observer observer(&engine);

    if (engine.status != 0) {
        return engine.status;
    }

    double delta_time;
    do {
        delta_time = engine.checkDeltaTime();
        engine.input_service();
        observer.move(delta_time);

        engine.drawing_begin();

//        engine.drawMap();

        engine.drawing_end();
    } while( engine.close_window_condition() );

    engine.cleanup();

    return 0;
}

