#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
// uniform sampler2D myTextureSampler;

void main(){
    color = vec3(1.0, 1.0, 1.0);
}
