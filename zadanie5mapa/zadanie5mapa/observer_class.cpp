// Include GLFW
#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "observer_class.hpp"

using namespace glm;

Observer::Observer(GraphicsEngine * engine) {
    // Initial position : on +Z
    position = vec3(0.0, 0.0, 0.0);
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;

    speed = 1.0f;           // per second
    mouseSpeed = 0.005f;

    this->engine = engine;
}

void Observer::move(double delta_time) {
    recalculate(float(delta_time));
    engine->VP = ProjectionMatrix * ViewMatrix;
}

void Observer::recalculate(float delta_time) {
    // Get mouse position
    int xpos, ypos;
    glfwGetMousePos(&xpos, &ypos);

    // Reset mouse position for next frame
    glfwSetMousePos(1000/2, 700/2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * float(1000/2 - xpos );
    verticalAngle   += mouseSpeed * float( 700/2 - ypos );

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    direction = vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    vec3 right = vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    // Up vector
    vec3 up = cross( right, direction );

    // Move forward
    if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * delta_time * speed;
    }
    // Move backward
    if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * delta_time * speed;
    }
    // Strafe right
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * delta_time * speed;
    }
    // Strafe left
    if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_D ) == GLFW_PRESS){
        position += right * delta_time * speed;
    }
    // Levitate up
    if (glfwGetKey( GLFW_KEY_R ) == GLFW_PRESS){
        position += up * delta_time * speed;
    }
    // Levitate down
    if (glfwGetKey( GLFW_KEY_F ) == GLFW_PRESS){
        position -= up * delta_time * speed;
    }

    float FoV = initialFoV - 5 * glfwGetMouseWheel();

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    ViewMatrix       = glm::lookAt(
                                position,           // Camera is here
                                position+direction, // and looks here : at the same position, plus "direction"
                                up                  // Head is up (set to 0,-1,0 to look upside-down)
                           );
    vec3 test1 = position + direction;
//    std::cout << "Pos" << position.x << " " << position.y << " " << position.z << std::endl;
//    std::cout << "Pos" << position.x << " " << position.y << " " << direction.z << std::endl;
//    std::cout << "Pos+dir" << test1.x << " " << test1.y << " " << test1.z << std::endl;
}
