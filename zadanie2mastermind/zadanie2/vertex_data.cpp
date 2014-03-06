#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>

#include "vertex_data.hpp"

#define PI  3.1415

// Element  From    To      Count
// Board:   0       31      32
// Fields:  32      271     240
// Cross:   272     275     4
// Results: 276     395     120
// Face:    396     577     182
// Eyes:    578     583     6
// Winner:  584     587     4
// Loser:   588     591     4

void vertex_data_initialization(GLfloat vertex_data[]) {
    int coord; //tmp

    // Board
    for (int i=0;i<11;i++) {
        vertex_data[6*i + 0] = -0.9f;
        vertex_data[6*i + 1] = 0.9f - i*0.17f;
        vertex_data[6*i + 2] = 0.0f;

        vertex_data[6*i + 3] = -0.1f;
        vertex_data[6*i + 4] = 0.9f - i*0.17f;
        vertex_data[6*i + 5] = 0.0f;
    }
    for (int i=11;i<16;i++) {
        vertex_data[6*i + 0] = -0.9f + (i-11)*0.2f;
        vertex_data[6*i + 1] = 0.9f;
        vertex_data[6*i + 2] = 0.0f;

        vertex_data[6*i + 3] = -0.9f + (i-11)*0.2f;
        vertex_data[6*i + 4] = -0.8f;
        vertex_data[6*i + 5] = 0.0f;
    }

    // Fields
    for (int i=0;i<10;i++) {
        for (int j=0;j<4;j++) {
            // 1 triangle, topleft corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 0] = -0.9f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 1] = 0.9f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 2] = 0.0f;

            // 1 triangle, topright corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 3] = -0.7f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 4] = 0.9f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 5] = 0.0f;

            // 1 triangle, bottomright corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 6] = -0.7f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 7] = 0.73f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 8] = 0.0f;

            // 2 triangle, topleft corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 9] = -0.9f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 10] = 0.9f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 11] = 0.0f;

            // 2 triangle, bottomleft corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 12] = -0.9f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 13] = 0.73f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 14] = 0.0f;

            // 2 triangle, bottomright corner, x y z
            vertex_data[(32 + (i*4 + j)*6)*3 + 15] = -0.7f + j * 0.2f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 16] = 0.73f - i * 0.17f;
            vertex_data[(32 + (i*4 + j)*6)*3 + 17] = 0.0f;
        }
    }

    // Result triangles
    for (int row=0;row<10;row++) {
        for (int col=0;col<4;col++) {
            int coord = 3*(276 + 3*(row*4 + col));
            vertex_data[coord + 0] = 0.0f + 0.2f * col;
            vertex_data[coord + 1] = 0.88f - 0.17f * row;
            vertex_data[coord + 2] = 0.0f;

            vertex_data[coord + 3] = 0.07f + 0.2f * col;
            vertex_data[coord + 4] = 0.75f - 0.17f * row;
            vertex_data[coord + 5] = 0.0f;

            vertex_data[coord + 6] = -0.07f + 0.2f * col;
            vertex_data[coord + 7] = 0.75f - 0.17f * row;
            vertex_data[coord + 8] = 0.0f;
        }
    }

    // Face
    coord = 3*396;
    vertex_data[coord + 0] = 0.0f;
    vertex_data[coord + 1] = 0.0f;
    vertex_data[coord + 2] = 0.0f;
    for (int i=1;i<=180;i++) {
        vertex_data[coord + 3*i + 0] = std::cos(2*i*PI / 180) * 0.5f;
        vertex_data[coord + 3*i + 1] = std::sin(2*i*PI / 180) * 0.7f;
        vertex_data[coord + 3*i + 2] = 0.0f;
    }
    vertex_data[coord + 3*181 + 0] = vertex_data[coord + 3*1 + 0];
    vertex_data[coord + 3*181 + 1] = vertex_data[coord + 3*1 + 1];
    vertex_data[coord + 3*181 + 2] = vertex_data[coord + 3*1 + 2];

    // Face 1st eye
    coord = 3*578;
    vertex_data[coord + 0] = -0.2f;
    vertex_data[coord + 1] = 0.5f;
    vertex_data[coord + 2] = 0.0f;
    vertex_data[coord + 3] = -0.3f;
    vertex_data[coord + 4] = 0.4f;
    vertex_data[coord + 5] = 0.0f;
    vertex_data[coord + 6] = -0.1f;
    vertex_data[coord + 7] = 0.4f;
    vertex_data[coord + 8] = 0.0f;

    // Face 2nd eye
    coord = 3*581;
    vertex_data[coord + 0] = 0.2f;
    vertex_data[coord + 1] = 0.5f;
    vertex_data[coord + 2] = 0.0f;
    vertex_data[coord + 3] = 0.3f;
    vertex_data[coord + 4] = 0.4f;
    vertex_data[coord + 5] = 0.0f;
    vertex_data[coord + 6] = 0.1f;
    vertex_data[coord + 7] = 0.4f;
    vertex_data[coord + 8] = 0.0f;

    // Winner face
    coord = 3*584;
    vertex_data[coord + 0] = -0.4f;
    vertex_data[coord + 1] = -0.1f;
    vertex_data[coord + 2] = 0.0f;
    vertex_data[coord + 3] = -0.2f;
    vertex_data[coord + 4] = -0.3f;
    vertex_data[coord + 5] = 0.0f;
    vertex_data[coord + 6] = 0.2f;
    vertex_data[coord + 7] = -0.3f;
    vertex_data[coord + 8] = 0.0f;
    vertex_data[coord + 9] = 0.4f;
    vertex_data[coord + 10] = -0.1f;
    vertex_data[coord + 11] = 0.0f;

    // Loser face
    coord = 3*588;
    vertex_data[coord + 0] = -0.4f;
    vertex_data[coord + 1] = -0.3f;
    vertex_data[coord + 2] = 0.0f;
    vertex_data[coord + 3] = -0.2f;
    vertex_data[coord + 4] = -0.1f;
    vertex_data[coord + 5] = 0.0f;
    vertex_data[coord + 6] = 0.2f;
    vertex_data[coord + 7] = -0.1f;
    vertex_data[coord + 8] = 0.0f;
    vertex_data[coord + 9] = 0.4f;
    vertex_data[coord + 10] = -0.3f;
    vertex_data[coord + 11] = 0.0f;
}

void color_data_initialization(GLfloat color_data[]) {
    int coord; //tmp
    // Board
    for (int i=0;i<32;i++) {
        color_data[3*i+0] = 1.0;
        color_data[3*i+1] = 1.0;
        color_data[3*i+2] = 1.0;
    }

    // Cross
    for (int i=272;i<276;i++) {
        color_data[3*i+0] = 1.0;
        color_data[3*i+1] = 1.0;
        color_data[3*i+2] = 1.0;
    }

    // Face
    coord = 3*396;
    for (int i=0;i<=181;i++) {
        color_data[coord + 3*i + 0] = 1.0f;
        color_data[coord + 3*i + 1] = 1.0f;
        color_data[coord + 3*i + 2] = 0.0f;
    }

    coord = 3*578;
    for (int i=0;i<14;i++) {
        color_data[coord + 3*i + 0] = 1.0f;
        color_data[coord + 3*i + 0] = 0.0f;
        color_data[coord + 3*i + 0] = 0.0f;
    }
}
