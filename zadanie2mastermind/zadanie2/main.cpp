// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <shader.hpp>
#include <vertex_data.hpp>

// Keycodes
#define GLFW_KEY_Q              81
#define GLFW_KEY_1              49
#define GLFW_KEY_2              50
#define GLFW_KEY_3              51
#define GLFW_KEY_4              52
#define GLFW_KEY_5              53
#define GLFW_KEY_6              54

void draw_cross(int current_column, int current_row, GLfloat vertex_data[]);
void keyboard_moving_left_right(int &current_column);
void keyboard_setting_colors(int fields[][4], GLfloat color_data[], int current_row, int current_column);
bool check_results(int final_result[], int final_result_colors[], int fields[][4], GLfloat color_data[], int results[][4], int current_row);

int main( void ) {
    // Generate seed
    srand(time(NULL));

    // Initialise GLFW
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    if(!glfwOpenWindow(1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW))
    {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetWindowTitle("Mastermind");

    // Ensure we can capture the escape key being pressed below
    glfwEnable(GLFW_STICKY_KEYS);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );


    // Data with vertex and colors
    static GLfloat vertex_data[3*592];
    vertex_data_initialization(vertex_data);
    static GLfloat color_data[3*592];
    color_data_initialization(color_data);

    // Mapping fields to colors, 0 - nothing, 1..6 - different colors
    int fields[10][4];
    // Results: 0 - nothing, 1 - black, 2 - white
    int results[10][4];

    for (int i=0;i<10;i++) {
        for (int j=0;j<4;j++) {
            fields[i][j] = 0;
            results[i][j] = 0;
        }
    }

    int final_result[4];
    int final_result_colors[7] = { 0 };
    for (int i=0;i<4;i++) {
        final_result[i] = (rand() % 6) + 1;
        final_result_colors[final_result[i]]++;
        std::cout << "Field " << i << ": " << final_result[i] << std::endl;
    }

    GLuint vertexbuffer, colorbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

    int current_row = 0;
    int current_column = 0;
    bool victory, game_over = false;

    do {
        if (!game_over) {
            keyboard_moving_left_right(current_column);
            draw_cross(current_column, current_row, vertex_data);
            keyboard_setting_colors(fields, color_data, current_row, current_column);
        }

        // checking the result
        if (glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS) {
            if (fields[current_row][0] && fields[current_row][1] && fields[current_row][2] && fields[current_row][3]) {
                if (check_results(final_result, final_result_colors, fields, color_data, results, current_row)) {
                    game_over = true;
                    victory = true;
                } else {
                    if (current_row == 9) {
                        game_over = true;
                        victory = false;
                    } else {
                        current_row++;
                    }
                }
            }
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        // Positions
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color_data), color_data, GL_STATIC_DRAW);
        glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw fields and results
        for (int i=0;i<10;i++) {
            for (int j=0;j<4;j++) {
                if (fields[i][j] != 0) {
                    glDrawArrays(GL_TRIANGLES, 32 + 6*(i*4 + j), 6);
                }

                if (results[i][j] != 0) {
                    glDrawArrays(GL_TRIANGLES, 276 + 3*(i*4 + j), 3);
                }
            }
        }

        glDrawArrays(GL_LINES, 0, 32); // Board
        if (game_over) {
            glDrawArrays(GL_TRIANGLE_FAN, 396, 182); // face
            glDrawArrays(GL_TRIANGLES, 578, 6); // eyes
            if (victory) {
                glDrawArrays(GL_LINE_STRIP, 588, 4); // loser face
            } else {
                glDrawArrays(GL_LINE_STRIP, 584, 4); // winner face
            }
        } else {
            glDrawArrays(GL_LINES, 272, 4); // Cross
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);


        // Swap buffers
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
           glfwGetKey(GLFW_KEY_Q) != GLFW_PRESS &&
           glfwGetWindowParam(GLFW_OPENED) );

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);

    return 0;
}

void keyboard_moving_left_right(int &current_column) {
    static bool left_pressed, right_pressed;

    // Moving left/right
    if (!left_pressed && (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)) {
        current_column--;
        left_pressed = true;
    }
    if (!right_pressed && (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)) {
        current_column++;
        right_pressed = true;
    }

    // Returning to released state if buttons released
    if (left_pressed && (glfwGetKey(GLFW_KEY_LEFT) == GLFW_RELEASE)) {
        left_pressed = false;
    }
    if (right_pressed && (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_RELEASE)) {
        right_pressed = false;
    }

    // We want current_column to be only from 0 to 3
    current_column %= 4;
    current_column += 4; // Because above accept -1, -2, -3 values as legal
    current_column %= 4;
}

bool check_results(int final_result[], int final_result_colors[], int fields[][4], GLfloat color_data[], int results[][4], int current_row) {
    int white_count = 0;
    int black_count = 0;
    int current_result_colors[7] = { 0 };

    // count black points and count amount of different colors in current result
    for (int i=0;i<4;i++) {
        if (final_result[i] == fields[current_row][i]) {
            black_count++;
        }

        current_result_colors[fields[current_row][i]]++;
    }

    // count white points
    for (int i=1;i<7;i++) {
        if (current_result_colors[i] > final_result_colors[i]) {
            white_count += final_result_colors[i];
        } else {
            white_count += current_result_colors[i];
        }
    }

    white_count -= black_count;

    if (black_count == 4) {
        // player won
        return true;
    }

    for (int i=0;i<4;i++) {
        if (black_count > 0) {
            // Draw black
            int coord = 3*(276 + 3*(current_row*4 + i));
            for (int j=0;j<9;j++) {
                color_data[coord + j] = 0.0f;
            }
            black_count--;
            results[current_row][i] = 1;
        } else if (white_count > 0) {
            // Draw white
            int coord = 3*(276 + 3*(current_row*4 + i));
            for (int j=0;j<9;j++) {
                color_data[coord + j] = 1.0f;
            }
            white_count--;
            results[current_row][i] = 2;
        }
    }

    return false;
}

void keyboard_setting_colors(int fields[][4], GLfloat color_data[], int current_row, int current_column) {
    if (glfwGetKey(GLFW_KEY_1) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 1;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 0.0f;
        }
    }

    if (glfwGetKey(GLFW_KEY_2) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 2;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 0.0f;
        }
    }

    if (glfwGetKey(GLFW_KEY_3) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 3;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 1.0f;
        }
    }

    if (glfwGetKey(GLFW_KEY_4) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 4;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 1.0f;
        }
    }

    if (glfwGetKey(GLFW_KEY_5) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 5;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 0.0f;
        }
    }

    if (glfwGetKey(GLFW_KEY_6) == GLFW_PRESS) {
        for (int k=0;k<6;k++) {
            fields[current_row][current_column] = 6;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 0] = 1.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 1] = 0.0f;
            color_data[(32 + (current_row*4 + current_column)*6 + k)*3 + 2] = 1.0f;
        }
    }
}

void draw_cross(int current_column, int current_row, GLfloat vertex_data[]) {
    // 1 line, topleft corner, x y z
    vertex_data[272*3 + 0] = -0.9f + current_column * 0.2f;
    vertex_data[272*3 + 1] = 0.9f - current_row * 0.17f;
    vertex_data[272*3 + 2] = -1.0f;

    // 1 line, bottomright corner, x y z
    vertex_data[273*3 + 0] = -0.7f + current_column * 0.2f;
    vertex_data[273*3 + 1] = 0.73f - current_row * 0.17f;
    vertex_data[273*3 + 2] = -1.0f;

    // 2 line, topright corner, x y z
    vertex_data[274*3 + 0] = -0.7f + current_column * 0.2f;
    vertex_data[274*3 + 1] = 0.9f - current_row * 0.17f;
    vertex_data[274*3 + 2] = -1.0f;

    // 2 line, bottomleft corner, x y z
    vertex_data[275*3 + 0] = -0.9f + current_column * 0.2f;
    vertex_data[275*3 + 1] = 0.73f - current_row * 0.17f;
    vertex_data[275*3 + 2] = -1.0f;
}

