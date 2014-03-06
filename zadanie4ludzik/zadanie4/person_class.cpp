#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "person_class.hpp"
#include "graphics_class.hpp"

using namespace glm;

#define PI      3.1415

Person::Person(GraphicsEngine *enginep) {
    engine = enginep;

    // Person settings, defaults
    move_angle          = 0.0f;
    speed               = vec3(4.0f * cos(2*PI*move_angle / 360), 0.0f, 4.0f * sin(2*PI*move_angle / 360));
    is_man              = true;
    arm_max_angle       = 10.0f;
    arm_speed           = 20.0f;
    forearm_max_angle   = 10.0f;
    forearm_speed       = 20.0f;
    leg_max_angle       = 30.0f;
    leg_speed           = 60.0f;
    leg_knee_mult       = 1.5f; // multiplier of leg_max_angle
    body_size           = vec3(0.6f, 1.8f, 0.8f);
    head_width          = 0.5f;
    neck_size           = vec3(0.2f, 0.1f, 0.2f);
    arm_length          = 0.7f;
    arm_height          = 0.2f;
    forearm_length      = 0.5f;
    leg_length          = 1.0f;
    leg_height          = 0.2f;
    calf_length         = 0.7f;
    foot_size           = vec3(0.4f, 0.1f, 0.2f);
    body_arm_offset     = 1.3f;
    leg_offset          = 0.5f;
    forearm_angle_offset= 10.0f;
    randomize_colors();


    // Person state, defaults
    position                    = vec3(0.0f, 0.0f, 0.0f);
    left_arm_angle              = arm_max_angle;
    left_arm_move_direction     = -1.0;
    right_arm_angle             = -arm_max_angle;
    right_arm_move_direction    = 1.0;
    left_forearm_angle          = forearm_max_angle;
    left_forearm_move_direction = -1.0;
    right_forearm_angle         = -forearm_max_angle;
    right_forearm_move_direction= 1.0;
    right_leg_angle             = leg_max_angle;
    right_leg_move_direction    = -1.0f;
    left_leg_angle              = -leg_max_angle;
    left_leg_move_direction     = 1.0f;
}

void Person::apply_physics(double delta_time) {
    // Movement
    position += ((float) delta_time) * speed;
    movement_y_translation = (leg_length + calf_length - 2*leg_height) * (cos(2*PI*right_leg_angle / 360) - 1);

    // Left arm
    if (left_arm_angle > arm_max_angle || left_arm_angle < -arm_max_angle) {
        left_arm_angle = left_arm_move_direction * arm_max_angle;
        left_arm_move_direction *= -1.0;
    }
    left_arm_angle += arm_speed * left_arm_move_direction * delta_time;

    // Left forearm
    if (left_forearm_angle > forearm_max_angle || left_forearm_angle < -forearm_max_angle) {
        left_forearm_angle = left_forearm_move_direction * forearm_max_angle;
        left_forearm_move_direction *= -1.0;
    }
    left_forearm_angle += forearm_speed * left_forearm_move_direction * delta_time;


    // Right arm
    if (right_arm_angle > arm_max_angle || right_arm_angle < -arm_max_angle) {
        right_arm_angle = right_arm_move_direction * arm_max_angle;
        right_arm_move_direction *= -1.0;
    }
    right_arm_angle += arm_speed * right_arm_move_direction * delta_time;

    // Right forearm
    if (right_forearm_angle > forearm_max_angle || right_forearm_angle < -forearm_max_angle) {
        right_forearm_angle = right_forearm_move_direction * forearm_max_angle;
        right_forearm_move_direction *= -1.0;
    }
    right_forearm_angle += forearm_speed * right_forearm_move_direction * delta_time;

    // Left leg
    if (left_leg_angle > leg_max_angle || left_leg_angle < -leg_max_angle) {
        left_leg_angle = left_leg_move_direction * leg_max_angle;
        left_leg_move_direction *= -1.0;
    }
    left_leg_angle += leg_speed * left_leg_move_direction * delta_time;
    if (left_leg_move_direction == 1.0) {
        left_calf_angle = leg_knee_mult*(abs(left_leg_angle) - leg_max_angle);
    }

    // Right leg
    if (right_leg_angle > leg_max_angle || right_leg_angle < -leg_max_angle) {
        right_leg_angle = right_leg_move_direction * leg_max_angle;
        right_leg_move_direction *= -1.0;
    }
    right_leg_angle += leg_speed * right_leg_move_direction * delta_time;
    if (right_leg_move_direction == 1.0) {
        right_calf_angle = leg_knee_mult*(abs(right_leg_angle) - leg_max_angle);
    }
}

void Person::draw(mat4 Init) {
    mat4 MVP = Init    * scale(1.0f, 1.0f, 1.0f)
                       * translate(position)
                       * translate(0.0f, movement_y_translation, 0.0f)
                       * rotate(-move_angle, vec3(0,1,0));
    draw_body(MVP);
}

void Person::draw_body(mat4 Init) {
    mat4 MVP = Init;
    mat4 MVPS = MVP * scale(body_size);
    engine->draw_body_part(MVPS, color_shirt);

    draw_neck(MVP);
    draw_arm(MVP, left_arm_angle, left_forearm_angle, 1.0);
    draw_arm(MVP, right_arm_angle, right_forearm_angle, -1.0);
    draw_right_leg(MVP);
    draw_left_leg(MVP);
}

void Person::draw_head(mat4 Init) {
    mat4 MVP = Init * translate(0.0f, head_width + neck_size.y, 0.0f);
    mat4 MVPS = MVP * scale(head_width, head_width, head_width);
    engine->draw_body_part(MVPS, color_skin);
}

void Person::draw_neck(mat4 Init) {
    mat4 MVP = Init * translate(0.0f, neck_size.y + body_size.y, 0.0f);
    mat4 MVPS = MVP * scale(neck_size);
    engine->draw_body_part(MVPS, color_skin);

    draw_head(MVP);
}

void Person::draw_arm(mat4 Init, GLfloat angle, GLfloat forearm_angle, GLfloat side) {
    mat4 MVP = Init    * translate(0.0f, body_arm_offset, side * (body_size.z + arm_height))
                       * rotate(angle, vec3(0, 0, 1))
                       * translate(0.0f, -arm_length, 0.0f);
    mat4 MVPS = MVP * scale(arm_height, arm_length, arm_height);
    engine->draw_body_part(MVPS, color_shirt);

    draw_forearm(MVP, forearm_angle);
}

void Person::draw_forearm(mat4 Init, GLfloat angle) {
    mat4 MVP = Init    * translate(0.0f, -arm_length, 0.0f)
                       * rotate(forearm_angle_offset + angle, vec3(0, 0, 1))
                       * translate(0.0f, -forearm_length, 0.0f);
    mat4 MVPS = MVP * scale(arm_height, forearm_length, arm_height);
    engine->draw_body_part(MVPS, color_sleeve);

    draw_hand(MVP);
}

void Person::draw_hand(mat4 Init) {
    mat4 MVP = Init    * translate(0.0f, -forearm_length, 0.0f)
                       * translate(0.0f, -arm_height, 0.0f);
    mat4 MVPS = MVP * scale(arm_height, arm_height, arm_height);
    engine->draw_body_part(MVPS, color_skin);
}

void Person::draw_right_leg(mat4 Init) {
    mat4 MVP = Init    * translate(0.0f, -(body_size.y - leg_height), leg_offset)
                       * rotate(right_leg_angle, vec3(0, 0, 1))
                       * translate(0.0f, -leg_length, 0.0f);
    mat4 MVPS = MVP * scale(leg_height, leg_length, leg_height);
    engine->draw_body_part(MVPS, color_shorts);

    draw_calf(MVP, right_calf_angle);
}

void Person::draw_left_leg(mat4 Init) {
    mat4 MVP = Init    * translate(0.0f, -(body_size.y - leg_height), -leg_offset)
                       * rotate(left_leg_angle, vec3(0, 0, 1))
                       * translate(0.0f, -leg_length, 0.0f);
    mat4 MVPS = MVP * scale(leg_height, leg_length, leg_height);
    engine->draw_body_part(MVPS, color_shorts);

    draw_calf(MVP, left_calf_angle);
}

void Person::draw_calf(mat4 Init, GLfloat angle) {
    mat4 MVP = Init    * translate(0.0f, -(leg_length - leg_height), 0.0f)
                       * rotate(angle, vec3(0, 0, 1))
                       * translate(0.0f, -calf_length, 0.0f);
    mat4 MVPS = MVP * scale(leg_height, calf_length, leg_height);
    engine->draw_body_part(MVPS, color_trousers);

    draw_foot(MVP);
}

void Person::draw_foot(glm::mat4 Init) {
    mat4 MVP = Init    * translate(0.0f, (-0.7f), 0.0f)
                       * translate(leg_height, -foot_size.y, 0.0f);
    mat4 MVPS = MVP * scale(foot_size);
    engine->draw_body_part(MVPS, color_shoes);
}

void Person::randomize_colors() {
    color_skin = engine->colors[YELLOW];
//    color_skin = engine->colors[rand() % 4];
    color_shirt = engine->colors[rand() % 9];
    if (rand() % 2) { // long sleeve
        color_sleeve = color_shirt;
    } else {
        color_sleeve = color_skin;
    }
    color_shorts = engine->colors[rand() % 9];
    if (rand() % 3) {
        color_trousers = color_skin;
    } else { // trousers
        color_trousers = color_shorts;
    }
    if (rand() % 2) {
        color_shoes = engine->colors[BROWN];
    } else {
        color_shoes = engine->colors[BLACK];
    }
}
