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

#include <shader.hpp>
#include <graphics_class.hpp>
#include <arkanoid_game.hpp>

using namespace glm;


int main() {
    // Generate seed
    srand(time(NULL));

    GraphicsEngine engine;
    if (engine.status != 0) {
        return engine.status;
    }
    engine.send_buffers();

    ArkanoidGame game(&engine);
    double delta_time;
    do {
        delta_time = engine.checkDeltaTime();

        game.apply_physics(delta_time);

        engine.drawing_begin();

        engine.draw_bg();
        engine.draw_bricks(game.cols, game.rows, game.bricks);
        engine.draw_ball(game.ball_pos.x, game.ball_pos.y);
        engine.draw_board(game.board_x);

        engine.drawing_end();


    } while( engine.close_window_condition() );

    engine.cleanup();

    return 0;
}

