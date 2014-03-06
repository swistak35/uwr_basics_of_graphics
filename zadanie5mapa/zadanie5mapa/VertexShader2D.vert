#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in float vertexHeight;

// uniform vec3 translation_vec;
uniform mat4 MVP;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

float depth;
vec3 color;

void main(){
    if (vertexHeight < 0) {
        depth = 0;
    } else {
//        depth = 0;
        depth = float(vertexHeight) * 0.001;
    }

//    gl_Position = MVP * vec4(vertexPosition.x / 1200, log(tan(vertexPosition.y / 2400)), depth, 1);
    gl_Position = MVP * vec4(vertexPosition.x * 0.001, vertexPosition.y * 0.001, depth, 1);
//    gl_Position = MVP * vec4(vertexPosition.y * 100, vertexPosition.x * 100, depth, 1);

    if      (vertexHeight < 0  )   color = vec3(0.,       0.,        1.);           // blue
    else if (vertexHeight < 500)   color = vec3(0.,       vertexHeight/500,    0.); // green
    else if (vertexHeight < 1000)  color = vec3(vertexHeight/500-1, 1.,        0.); // yellow
    else if (vertexHeight < 1500)  color = vec3(1.,       2.-vertexHeight/500, 0.); // red
    else                           color = vec3(1.,1.,1.);                          // white

    fragmentColor = color;
}
