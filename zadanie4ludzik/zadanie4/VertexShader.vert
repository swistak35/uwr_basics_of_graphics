#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
// uniform vec3 translation_vec;
uniform mat4 MVP;
uniform vec3 modcolor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    fragmentColor = modcolor;
}
