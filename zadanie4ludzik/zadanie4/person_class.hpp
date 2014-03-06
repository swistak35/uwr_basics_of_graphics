#ifndef PERSON_CLASS_HPP
#define PERSON_CLASS_HPP

#include <glm/glm.hpp>
#include "graphics_class.hpp"

using namespace glm;

class Person {
public:
    GraphicsEngine * engine;

    // Person state
    vec3 position;
    GLfloat left_arm_angle;
    GLfloat left_arm_move_direction;
    GLfloat left_forearm_angle;
    GLfloat left_forearm_move_direction;
    GLfloat right_arm_angle;
    GLfloat right_arm_move_direction;
    GLfloat right_forearm_angle;
    GLfloat right_forearm_move_direction;
    GLfloat right_leg_angle;
    GLfloat right_leg_move_direction;
    GLfloat right_calf_angle;
    GLfloat left_leg_angle;
    GLfloat left_leg_move_direction;
    GLfloat left_calf_angle;
    GLfloat movement_y_translation;

    // Person settings
    vec3 speed;
    bool is_man;
    GLfloat arm_max_angle;
    GLfloat arm_speed;
    GLfloat forearm_max_angle;
    GLfloat forearm_speed;
    GLfloat leg_max_angle;
    GLfloat leg_speed;
    GLfloat leg_knee_mult;
    vec3 body_size;
    GLfloat head_width;
    vec3 neck_size;
    GLfloat arm_length;
    GLfloat arm_height;
    GLfloat forearm_length;
    GLfloat leg_length;
    GLfloat leg_height;
    GLfloat calf_length;
    vec3 foot_size;
    GLfloat body_arm_offset;
    GLfloat leg_offset;
    GLfloat forearm_angle_offset;
    GLfloat move_angle;
    vec3 color_skin;
    vec3 color_shirt;
    vec3 color_sleeve;
    vec3 color_shorts;
    vec3 color_trousers;
    vec3 color_shoes;

    // API
    Person(GraphicsEngine * engine);
    void apply_physics(double delta_time);
    void randomize_colors();

    // Drawing
    void draw(mat4 Init);
private:
    void draw_head(mat4 Init);
    void draw_neck(mat4 Init);
    void draw_body(mat4 Init);
    void draw_arm(mat4 Init, GLfloat angle, GLfloat forearm_angle, GLfloat side);
    void draw_forearm(mat4 Init, GLfloat angle);
    void draw_hand(mat4 Init);
    void draw_right_leg(mat4 Init);
    void draw_left_leg(mat4 Init);
    void draw_calf(mat4 Init, GLfloat angle);
    void draw_foot(mat4 Init);
};

#endif
