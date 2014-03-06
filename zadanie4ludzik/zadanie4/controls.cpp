// Include GLFW
#include <GL/glfw.h>
#include <iostream>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

#define 	GLFW_KEY_A   65
#define 	GLFW_KEY_D   68
#define 	GLFW_KEY_F   70
#define 	GLFW_KEY_R   82
#define 	GLFW_KEY_S   83
#define 	GLFW_KEY_W   87


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 10.0f; // 3 units / second
float mouseSpeed = 0.005f;


void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	int xpos, ypos;
	glfwGetMousePos(&xpos, &ypos);

	// Reset mouse position for next frame
    glfwSetMousePos(1000/2, 700/2);

	// Compute new orientation
    horizontalAngle += mouseSpeed * float(1000/2 - xpos );
    verticalAngle   += mouseSpeed * float( 700/2 - ypos );

//    std::cout << "mouse at (" << xpos << ", " << ypos << ")\n";

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
		0,
        cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
    if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_W ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
    if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_S ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
	}
	// Strafe left
    if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS || glfwGetKey( GLFW_KEY_D ) == GLFW_PRESS){
        position += right * deltaTime * speed;
	}
    // Levitate up
    if (glfwGetKey( GLFW_KEY_R ) == GLFW_PRESS){
        position += up * deltaTime * speed;
    }
    // Levitate down
    if (glfwGetKey( GLFW_KEY_F ) == GLFW_PRESS){
        position -= up * deltaTime * speed;
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

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}