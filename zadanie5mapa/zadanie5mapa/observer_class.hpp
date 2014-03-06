#ifndef OBSERVER_CLASS_HPP
#define OBSERVER_CLASS_HPP

#include "utils.hpp"
#include "graphics_class.hpp"

#define 	GLFW_KEY_A          65
#define 	GLFW_KEY_D          68
#define 	GLFW_KEY_F          70
#define 	GLFW_KEY_R          82
#define 	GLFW_KEY_S          83
#define 	GLFW_KEY_W          87
#define     GLFW_KEY_PERIOD     46
#define     GLFW_KEY_COMMA      44

using namespace glm;

class Observer {
public:
    GraphicsEngine * engine;
    vec3 position;
    vec3 direction;
    vec3 up;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    float speed;
    float mouseSpeed;
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;

    Observer(GraphicsEngine * engine);
    void move(double delta_time);
    void recalculate(float delta_time);
};


#endif

