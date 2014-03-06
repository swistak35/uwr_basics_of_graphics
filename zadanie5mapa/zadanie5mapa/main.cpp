#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "globe_class.hpp"
#include "graphics_class.hpp"
#include "observer_class.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Nie podałeś pliku z mapami.\n";
        return -1;
    }

    int mode = 2;
    for (int i=1; i < argc; i++) {
        if (strcmp(argv[i],"--3d") == 0) {
            mode = 3;
        }
    }
    cout << "Mode: " << mode << "D\n";

    GraphicsEngine engine(mode);
    Observer observer(&engine);
    Globe globe(argv[1], &engine, &observer);

    if (engine.status != 0) {
        return engine.status;
    }

    double delta_time;
    do {
        delta_time = engine.checkDeltaTime();
        engine.input_service();
        observer.move(delta_time);

        engine.drawing_begin();

        engine.drawMap();

        engine.drawing_end();
    } while( engine.close_window_condition() );

    engine.cleanup();

    return 0;
}

