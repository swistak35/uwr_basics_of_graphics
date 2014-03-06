#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "arkanoid_game.hpp"

using namespace glm;

#define PI                  3.1415

ArkanoidGame::ArkanoidGame(GraphicsEngine * enginet) {
    engine = enginet;
    engine->fetch_data(cols,rows);

    for (int i=0;i<cols;i++) {
        for (int j=0;j<rows;j++) {
            bricks[i*rows + j] = true;
        }
    }

    board_x = 0.0;
    reset_ball();
}

void ArkanoidGame::reset_ball() {
    ball_pos.x = 0.0;
    ball_pos.y = 0.0;
    ball_direction.x = cos(1.5 * PI);
    ball_direction.y = sin(1.5 * PI);
}

void ArkanoidGame::apply_physics(double time) {
    vec2 ball_edge_move;
    bool move_ball = true;

    switch (engine->is_arrow_pressed()) {
        case  1: move_board(board_speed * time); break;
        case -1: move_board(- board_speed * time); break;
    }

    ball_edge_move.x = ball_pos.x + engine->ball_radius * ball_direction.x * engine->window_ratio + ball_direction.x * ball_speed * time * engine->window_ratio;
    ball_edge_move.y = ball_pos.y + engine->ball_radius * ball_direction.y + ball_direction.y * ball_speed * time;

    if (check_board_collisions(ball_edge_move) || check_bricks_collisions(ball_edge_move) || check_wall_collisions(ball_edge_move)) {
        move_ball = false;
    }

    if (move_ball) {
        ball_pos.x += ball_direction.x * ball_speed * time * engine->window_ratio;
        ball_pos.y += ball_direction.y * ball_speed * time;
    }
}

bool ArkanoidGame::check_wall_collisions(vec2 ball_edge_move) {
    if (ball_edge_move.x < -1.0 || ball_edge_move.x > 1.0) {
        ball_bounce_vertically();
        return true;
    } else if (ball_edge_move.y > 1.0) {
        ball_bounce_horizontally();
        return true;
    } else if (ball_edge_move.y < -1.0) {
        reset_ball();
        return true;
    }
    return false;
}

bool ArkanoidGame::check_board_collisions(vec2 ball_edge_move) {
    if (ball_edge_move.y < -0.8f && ball_pos.y > -0.8f && ball_edge_move.x <= board_x + engine->board_width/2 + engine->ball_radius && ball_edge_move.x >= board_x - engine->board_width/2 - engine->ball_radius) {
        ball_bounce_horizontally();
        return true;
    }
    return false;
}

bool ArkanoidGame::check_bricks_collisions(vec2 ball_edge_move) {
    vec2 tmp;
    GLfloat top, bottom, left, right;
    for (int i=0;i<cols;i++) {
        for (int j=0;j<rows;j++) {
            if (bricks[i*rows + j]) {
                tmp = engine->get_brick_pos(i, j);
                left = tmp.x;
                top = tmp.y;
                right = tmp.x + engine->brick_ext_width;
                bottom = tmp.y - engine->brick_ext_height;

                if (ball_edge_move.y > bottom && ball_pos.y < bottom && ball_edge_move.x <= right && ball_edge_move.x >= left) {
                    ball_bounce_horizontally();
                    bricks[i*rows + j] = false;
                    return true;
                }

                if (ball_edge_move.y < top && ball_pos.y > top && ball_edge_move.x <= right && ball_edge_move.x >= left) {
                    ball_bounce_horizontally();
                    bricks[i*rows + j] = false;
                    return true;
                }

                if (ball_edge_move.x > left && ball_pos.x < left && ball_edge_move.y <= top && ball_edge_move.y >= bottom) {
                    ball_bounce_vertically();
                    bricks[i*rows + j] = false;
                    return true;
                }

                if (ball_edge_move.x < right && ball_pos.x > right && ball_edge_move.y <= top && ball_edge_move.y >= bottom) {
                    ball_bounce_vertically();
                    bricks[i*rows + j] = false;
                    return true;
                }
            }
        }
    }
    return false;
}

void ArkanoidGame::ball_bounce_vertically() {
    ball_direction.x = - ball_direction.x;
    ball_direction.y = ball_direction.y + ((rand() % 21) * 0.01 - 0.1);
    ball_direction = normalize(ball_direction);
}

void ArkanoidGame::ball_bounce_horizontally() {
    ball_direction.y = - ball_direction.y;
    ball_direction.x = ball_direction.x + ((rand() % 21) * 0.01 - 0.1);
    ball_direction = normalize(ball_direction);
}


void ArkanoidGame::move_board(double shift) {
    static GLfloat right_border = 1.0 - (engine->board_height * engine->window_ratio);
    static GLfloat left_border  = -1.0 + (engine->board_height * engine->window_ratio);

    board_x += shift;
    if (board_x > right_border) board_x = right_border;
    if (board_x < left_border) board_x = left_border;
}
