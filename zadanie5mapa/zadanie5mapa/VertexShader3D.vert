#version 330 core

const float angles = 0.017453292519943295;
const float base_radius = 10.0;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in float vertexHeight;

// uniform vec3 translation_vec;
uniform mat4 MVP;
uniform vec3 mod_color;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

//float depth;
float x,y,z;
vec3 color;
float radius, depth;

void main(){
    if (vertexHeight < 0) {
        depth = 0;
    } else {
//        depth = 0;
//        depth = float(vertexHeight) * 0.0001;
        depth = float(vertexHeight) * 0.0000015696123057604772;
    }
    radius = base_radius + depth;
    x = radius * sin(vertexPosition.x * angles) * cos(vertexPosition.y * angles);
    y = radius * sin(vertexPosition.x * angles) * sin(vertexPosition.y * angles);
    z = radius * cos(vertexPosition.x * angles);
    gl_Position = MVP * vec4(x, y, z, 1);

    if      (vertexHeight < 0  )   color = vec3(0.,       0.,        1.);           // blue
    else if (vertexHeight < 500)   color = vec3(0.,       vertexHeight/500,    0.); // green
    else if (vertexHeight < 1000)  color = vec3(vertexHeight/500-1, 1.,        0.); // yellow
    else if (vertexHeight < 1500)  color = vec3(1.,       2.-vertexHeight/500, 0.); // red
    else                           color = vec3(1.,1.,1.);                          // white

    fragmentColor = color + mod_color;
}
