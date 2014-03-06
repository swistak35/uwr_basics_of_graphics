#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include <shader.hpp>

#include "graphics_class.hpp"

#define PI                  3.1415
#define GLFW_KEY_Q          81

using namespace glm;

void GraphicsEngine::initialize_buffers() {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
}

void GraphicsEngine::initialize_brick_data() {
    int vsize = vertices.size();
    brick_location = (void*)(indices.size() * sizeof(unsigned int));

    vtx topleft_ext_corner = { 0.0, 0.0, 0.0, 1.0, 1.0, 0.0 };
    vtx topright_ext_corner = { brick_ext_width, 0.0, 0.0, 1.0, 1.0, 0.0 };
    vtx bottomleft_ext_corner = { 0.0, - brick_ext_height, 0.0, 1.0, 1.0, 0.0 };
    vtx bottomright_ext_corner = { brick_ext_width, -brick_ext_height, 0.0, 1.0, 1.0, 0.0 };

    vtx topleft_int_corner = {
        (brick_ext_width - brick_int_width) / 2,
        -(brick_ext_height - brick_int_height) / 2,
        0.0, 1.0, 0.0, 0.0
    };

    vtx topright_int_corner = {
        (brick_ext_width - brick_int_width) / 2 + brick_int_width,
        -(brick_ext_height - brick_int_height) / 2,
        0.0, 1.0, 0.0, 0.0
    };

    vtx bottomleft_int_corner = {
        (brick_ext_width - brick_int_width) / 2,
        -(brick_ext_height - brick_int_height) / 2 - brick_int_height,
        0.0, 1.0, 0.0, 0.0
    };

    vtx bottomright_int_corner = {
        (brick_ext_width - brick_int_width) / 2 + brick_int_width,
        -(brick_ext_height - brick_int_height) / 2 - brick_int_height,
        0.0, 1.0, 0.0, 0.0
    };

    vertices.push_back(topleft_ext_corner);
    vertices.push_back(topright_ext_corner);
    vertices.push_back(bottomleft_ext_corner);
    vertices.push_back(bottomright_ext_corner);

    vertices.push_back(topleft_int_corner);
    vertices.push_back(topright_int_corner);
    vertices.push_back(bottomleft_int_corner);
    vertices.push_back(bottomright_int_corner);


    indices.push_back(vsize);
    indices.push_back(vsize+1);
    indices.push_back(vsize+2);

    indices.push_back(vsize+1);
    indices.push_back(vsize+2);
    indices.push_back(vsize+3);

    indices.push_back(vsize+4);
    indices.push_back(vsize+5);
    indices.push_back(vsize+6);

    indices.push_back(vsize+5);
    indices.push_back(vsize+6);
    indices.push_back(vsize+7);
}



GraphicsEngine::GraphicsEngine() {
    status = initialize_opengl();
    initialize_buffers();
    initialize_bg_data();
    initialize_ball_data();
    initialize_brick_data();
    initialize_board_data();

    last_time = glfwGetTime();
}

int GraphicsEngine::initialize_opengl() {
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
    if(!glfwOpenWindow(window_width, window_height, 0,0,0,0, 32,0, GLFW_WINDOW))
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

    glfwSetWindowTitle("Arkanoid");

    // Ensure we can capture the escape key being pressed below
    glfwEnable(GLFW_STICKY_KEYS);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "VertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

    return 0;
}

void GraphicsEngine::send_buffers() {
    glUseProgram(programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        sizeof(vtx),        // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        sizeof(vtx),        // stride
        (void*)(3*sizeof(GLfloat))            // array buffer offset
    );

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vtx), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void GraphicsEngine::draw_bricks(int cols, int rows, bool bricks[]) {
    vec2 res;
    for (int i=0;i<cols;i++) {
        for (int j=0;j<rows;j++) {
            if (bricks[i*rows + j]) {
                res = get_brick_pos(i, j);
                glUniform3f(glGetUniformLocation(programID, "translation_vec"), res.x, res.y, 0.0f);
                glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, brick_location);
            }
        }
    }
}

void GraphicsEngine::fetch_data(int cols, int rows) {
    brick_offset_x = (2.0 - cols * brick_ext_width - (cols-1)*0.01) / 2;
}

vec2 GraphicsEngine::get_brick_pos(int col, int row) {
    return vec2(-1 + brick_offset_x + col*(brick_ext_width + 0.01), 1 - brick_offset_y - row*(brick_ext_height + 0.01));
}

void GraphicsEngine::initialize_ball_data() {
    int vsize = vertices.size();
    ball_location = (void*)(indices.size() * sizeof(unsigned int));

    vertices.push_back({ 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 });
    indices.push_back(vsize);

    for (int i=1;i<=ball_precision;i++) {
        vertices.push_back({
            (GLfloat) (std::cos(2*i*PI / ball_precision) * ball_radius),
            (GLfloat) (std::sin(2*i*PI / ball_precision) * ball_radius * window_ratio),
            0.0,
            0.0,
            1.0,
            0.0
        });
        indices.push_back(vsize+i);
    }

    indices.push_back(vsize+1);
}

bool GraphicsEngine::close_window_condition() {
    return (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
            glfwGetKey(GLFW_KEY_Q) != GLFW_PRESS &&
            glfwGetWindowParam(GLFW_OPENED));
}

void GraphicsEngine::draw_ball(GLfloat x, GLfloat y) {
    glUniform3f(glGetUniformLocation(programID, "translation_vec"), x, y, 0.0f);
    glDrawElements(GL_TRIANGLE_FAN, ball_precision+2, GL_UNSIGNED_INT, ball_location);
}

void GraphicsEngine::initialize_board_data() {
    int vsize = vertices.size();
    board_location = (void*)(indices.size() * sizeof(unsigned int));

    vertices.push_back({
        board_width / 2,
        board_y_position,
        0.0,
        1.0,
        0.0,
        0.0
    });

    vertices.push_back({
        - board_width / 2,
        board_y_position,
        0.0,
        1.0,
        0.0,
        0.0
    });

    vertices.push_back({
        board_width / 4,
        board_y_position - board_height,
        0.0,
        1.0,
        0.0,
        0.0
    });

    vertices.push_back({
        - board_width / 4,
        board_y_position - board_height,
        0.0,
        1.0,
        0.0,
        0.0
    });

    indices.push_back(vsize);
    indices.push_back(vsize+1);
    indices.push_back(vsize+2);

    indices.push_back(vsize+1);
    indices.push_back(vsize+2);
    indices.push_back(vsize+3);
}

void GraphicsEngine::draw_board(GLfloat translation) {
    glUniform3f(glGetUniformLocation(programID, "translation_vec"), translation, 0.0, 0.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, board_location);
}

void GraphicsEngine::initialize_bg_data() {
    int vsize = vertices.size();
    bg_location = (void*)(indices.size() * sizeof(unsigned int));
    GLfloat tmp = bg_hex_height / sqrt(3);

    vertices.push_back({ tmp, bg_hex_height * window_ratio, 0.0, 0.0, 0.3, 0.6 });
    vertices.push_back({ 2*tmp, 0.0, 0.0, 0.0, 0.3, 0.6 });
    vertices.push_back({ tmp, -bg_hex_height * window_ratio, 0.0, 0.0, 0.3, 0.6 });
    vertices.push_back({ -tmp, -bg_hex_height * window_ratio, 0.0, 0.0, 0.3, 0.6 });
    vertices.push_back({ -2*tmp, 0.0, 0.0, 0.0, 0.3, 0.6 });
    vertices.push_back({ -tmp, bg_hex_height * window_ratio, 0.0, 0.0, 0.3, 0.6 });

    indices.push_back(vsize);
    indices.push_back(vsize+1);
    indices.push_back(vsize+2);
    indices.push_back(vsize+3);
    indices.push_back(vsize+4);
    indices.push_back(vsize+5);
    indices.push_back(vsize);
}

void GraphicsEngine::draw_bg() {
    GLfloat tmpx, tmpy, width = bg_hex_height / sqrt(3);

    int amountx = int(0.5 / width);
    int amounty = int(0.5 / (bg_hex_height * window_ratio)) + 1;

    for (int j=0;j<2*amountx;j++) {
        if (j % 2 == 0) {
            tmpx = 3*width*(j - amountx);
        } else {
            tmpx = 3*width + 3*width*(j-amountx-1);
        }

        for (int i=0;i<2*amounty;i++) {
            if (j % 2 == 0) {
                tmpy = 2*bg_hex_height*window_ratio*(i - amounty);
            } else {
                tmpy = 2*bg_hex_height*window_ratio*(i - amounty) + bg_hex_height*window_ratio;
            }
            glUniform3f(glGetUniformLocation(programID, "translation_vec"), tmpx, tmpy, 0.0);
            glDrawElements(GL_LINE_STRIP, 7, GL_UNSIGNED_INT, bg_location);
        }
    }
}

void GraphicsEngine::cleanup() {
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
}

int GraphicsEngine::is_arrow_pressed() {
    int res = 0;
    if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
        res++;
    }
    if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
        res--;
    }
    return res;
}

double GraphicsEngine::checkDeltaTime() {
    current_time = glfwGetTime();
    double delta_time = current_time - last_time;
    last_time = current_time;
    return delta_time;
}

void GraphicsEngine::drawing_begin() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
}

void GraphicsEngine::drawing_end() {
    glfwSwapBuffers();
}
