// Include standard headers
#include <stdlib.h>
#include <iostream>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>

#include "shader.hpp"
#include "person_class.hpp"
#include "graphics_class.hpp"
#include "crowd_class.hpp"

using namespace glm;

int main()
{
    srand(time(NULL));

    GraphicsEngine engine;
    if (engine.status != 0) {
        return engine.status;
    }
    engine.send_buffers();

    Crowd crowd(&engine);
    double delta_time;
    do {
        delta_time = engine.checkDeltaTime();

        crowd.apply_physics(delta_time);

        engine.drawing_begin();

        crowd.draw_people();

        engine.drawing_end();
    } while( engine.close_window_condition() );

    engine.cleanup();
    return 0;
}

