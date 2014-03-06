#ifndef ARKANOID_GAME_CLASS_HPP
#define ARKANOID_GAME_CLASS_HPP

#include <graphics_class.hpp>
#include <glm/glm.hpp>
using namespace glm;

class ArkanoidGame {
public:
    GraphicsEngine * engine;
    ArkanoidGame(GraphicsEngine * enginet);
    void reset_ball();
    void apply_physics(double time);
    void move_board(double shift);
    bool check_collision(vec2 a1, vec2 a2, vec2 b1, vec2 b2, vec2 * result);
    void ball_bounce_vertically();
    void ball_bounce_horizontally();
    bool check_board_collisions(vec2 ball_edge_move);
    bool check_bricks_collisions(vec2 ball_edge_move);
    bool check_wall_collisions(vec2 ball_edge_move);

    // Bricks data
    static constexpr int cols = 13;
    static constexpr int rows = 7;
    bool bricks[cols * rows];

    // Ball data
    vec2 ball_direction;
    vec2 ball_pos;
    static constexpr GLfloat ball_speed = 0.9;

    // Board data
    static constexpr GLfloat board_speed = 0.9;
    GLfloat board_x;
};


#endif
