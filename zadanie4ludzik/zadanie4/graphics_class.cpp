#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <shader.hpp>
#include "controls.hpp"

#include "graphics_class.hpp"
#include "person_class.hpp"

#define PI                  3.1415
#define GLFW_KEY_V   86

using namespace glm;

void GraphicsEngine::initialize_buffers() {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
}

void GraphicsEngine::initialize_cube_data() {
    int vsize = vertices.size();
    cube_location = (void*)(indices.size() * sizeof(unsigned int));

    vtx top_left_front  = { -1.0,  1.0,  1.0, 0.0, 0.0, 0.0 };
    vtx top_right_front = {  1.0,  1.0,  1.0, 0.0, 0.0, 0.0 };
    vtx btm_left_front  = { -1.0, -1.0,  1.0, 0.0, 0.0, 0.0 };
    vtx btm_right_front = {  1.0, -1.0,  1.0, 0.0, 0.0, 0.0 };

    vtx top_left_back   = { -1.0,  1.0, -1.0, 0.0, 0.0, 0.0 };
    vtx top_right_back  = {  1.0,  1.0, -1.0, 0.0, 0.0, 0.0 };
    vtx btm_left_back   = { -1.0, -1.0, -1.0, 0.0, 0.0, 0.0 };
    vtx btm_right_back  = {  1.0, -1.0, -1.0, 0.0, 0.0, 0.0 };

    vertices.push_back(top_left_front);
    vertices.push_back(top_right_front);
    vertices.push_back(btm_left_front);
    vertices.push_back(btm_right_front);

    vertices.push_back(top_left_back);
    vertices.push_back(top_right_back);
    vertices.push_back(btm_left_back);
    vertices.push_back(btm_right_back);

    //    przod: (tlf, trf, blf), (blf, brf, trf),
    indices.push_back(vsize+0);
    indices.push_back(vsize+1);
    indices.push_back(vsize+2);

    indices.push_back(vsize+2);
    indices.push_back(vsize+3);
    indices.push_back(vsize+1);

    //    prawa: (trf, trb, brf), (trb, brf, brb),
    indices.push_back(vsize+1);
    indices.push_back(vsize+5);
    indices.push_back(vsize+3);

    indices.push_back(vsize+5);
    indices.push_back(vsize+3);
    indices.push_back(vsize+7);

    //    tyl:   (tlb, trb, blb), (blb, brb, trb),
    indices.push_back(vsize+4);
    indices.push_back(vsize+5);
    indices.push_back(vsize+6);

    indices.push_back(vsize+6);
    indices.push_back(vsize+7);
    indices.push_back(vsize+5);

    //    lewa:  (tlf, tlb, blf), (tlb, blf, blb),
    indices.push_back(vsize+0);
    indices.push_back(vsize+4);
    indices.push_back(vsize+2);

    indices.push_back(vsize+4);
    indices.push_back(vsize+2);
    indices.push_back(vsize+6);

    //    gora:  (tlf, trf, trb), (tlf, tlb, trb),
    indices.push_back(vsize+0);
    indices.push_back(vsize+1);
    indices.push_back(vsize+5);

    indices.push_back(vsize+0);
    indices.push_back(vsize+4);
    indices.push_back(vsize+5);

    //    dol:   (blf, brf, brb), (blf, blb, brb),
    indices.push_back(vsize+2);
    indices.push_back(vsize+3);
    indices.push_back(vsize+7);

    indices.push_back(vsize+2);
    indices.push_back(vsize+6);
    indices.push_back(vsize+7);

    vsize = vertices.size();
    cube_sketch_location = (void*)(indices.size() * sizeof(unsigned int));

    vtx top_left_fronts  = { -1.0,  1.0,  1.0, 1.0, 1.0, 1.0 };
    vtx top_right_fronts = {  1.0,  1.0,  1.0, 1.0, 1.0, 1.0 };
    vtx btm_left_fronts  = { -1.0, -1.0,  1.0, 1.0, 1.0, 1.0 };
    vtx btm_right_fronts = {  1.0, -1.0,  1.0, 1.0, 1.0, 1.0 };

    vtx top_left_backs   = { -1.0,  1.0, -1.0, 1.0, 1.0, 1.0 };
    vtx top_right_backs  = {  1.0,  1.0, -1.0, 1.0, 1.0, 1.0 };
    vtx btm_left_backs   = { -1.0, -1.0, -1.0, 1.0, 1.0, 1.0 };
    vtx btm_right_backs  = {  1.0, -1.0, -1.0, 1.0, 1.0, 1.0 };

    vertices.push_back(top_left_fronts);
    vertices.push_back(top_right_fronts);
    vertices.push_back(btm_left_fronts);
    vertices.push_back(btm_right_fronts);

    vertices.push_back(top_left_backs);
    vertices.push_back(top_right_backs);
    vertices.push_back(btm_left_backs);
    vertices.push_back(btm_right_backs);

    indices.push_back(vsize+0);
    indices.push_back(vsize+1);
    indices.push_back(vsize+3);
    indices.push_back(vsize+2);
    indices.push_back(vsize+0);

    indices.push_back(vsize+4);
    indices.push_back(vsize+5);
    indices.push_back(vsize+7);
    indices.push_back(vsize+6);
    indices.push_back(vsize+4);

    indices.push_back(vsize+6);
    indices.push_back(vsize+2);
    indices.push_back(vsize+3);
    indices.push_back(vsize+7);
    indices.push_back(vsize+5);
    indices.push_back(vsize+1);

    colors[YELLOW] = vec3(1.0, 1.0, 0.0);
    colors[RED] = vec3(1.0, 0.0, 0.0);
    colors[GREEN] = vec3(0.0, 1.0, 0.0);
    colors[BLUE] = vec3(0.0, 0.0, 1.0);
    colors[WHITE] = vec3(1.0, 1.0, 1.0);
    colors[BLACK] = vec3(0.0, 0.0, 0.0);
    colors[CYAN] = vec3(0.0, 1.0, 1.0);
    colors[BROWN] = vec3(0.4, 0.2, 0.0);
    colors[MAGENTA] = vec3(1.0, 0.0, 1.0);
}



GraphicsEngine::GraphicsEngine() {
    status = initialize_opengl();
    initialize_buffers();
    initialize_cube_data();

    last_time = glfwGetTime();
    current_view = 1;
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

    glfwSetWindowTitle("Ludziki");

    // Ensure we can capture the escape key being pressed below
    glfwEnable(GLFW_STICKY_KEYS);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "VertexShader.vert", "ColorFragmentShader.frag" );

    glfwSetMousePos(1000/2, 700/2);
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

bool GraphicsEngine::close_window_condition() {
    return (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
            glfwGetWindowParam(GLFW_OPENED));
}

void GraphicsEngine::draw_cube() {
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View = lookAt(   vec3(4,3,-3),
                               vec3(0,0,0),
                               vec3(0,1,0)
                           );
    mat4 Model = mat4(1.0f);
    mat4 Cuber = scale(1.0f, window_ratio, 1.0f);
    mat4 Scale = scale(0.5f, 0.5f, 0.5f);

    mat4 MVP = Projection * View * Model * Cuber * Scale;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, cube_location);
    glDrawElements(GL_LINE_STRIP, 16, GL_UNSIGNED_INT, cube_sketch_location);

}

mat4 GraphicsEngine::getMVP() {
    mat4 VP;
    switch (current_view) {
        case 0: VP = getMovingVP(); break;
        case 1: VP = getUpVP(); break;
        case 2: VP = get1PersonVP(); break;
        case 3: VP = get3PersonVP(); break;
    }

    mat4 Model = mat4(1.0f);
    mat4 MVP = VP * Model;

    return MVP;
}

mat4 GraphicsEngine::getMovingVP() {
    computeMatricesFromInputs();
    mat4 Projection = getProjectionMatrix();
    mat4 View = getViewMatrix();
    return (Projection * View);
}

mat4 GraphicsEngine::get1PersonVP() {
    vec3 obs_head = vec3(observer->position.x, (observer->position.y + (observer->body_size).y + observer->head_width), observer->position.z);
    GLfloat angle = 2*PI*observer->move_angle / 360;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View       = lookAt(
                                obs_head + vec3(observer->head_width * cos(angle), 0.0f, observer->head_width * sin(angle)),
                                obs_head + vec3(10.0f * cos(angle), 0.0f, 10.0f * sin(angle)),
                                vec3(0,1,0)
                            );
    return (Projection * View);
}

mat4 GraphicsEngine::get3PersonVP() {
    vec3 obs_head = vec3(observer->position.x, (observer->position.y + (observer->body_size).y + observer->head_width), observer->position.z);
    GLfloat angle = 2*PI*observer->move_angle / 360;
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View       = lookAt(
                                obs_head + vec3((-6.0f) * cos(angle), 3.0f, (-6.0f) * sin(angle)),
                                obs_head,
                                vec3(0,1,0)
                            );
    return (Projection * View);
}

mat4 GraphicsEngine::getUpVP() {
    mat4 Projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View       = lookAt(
                                vec3(-1,30,-1),
                                vec3(20,0,0),
                                vec3(0,1,0)
                            );
    return (Projection * View);
}

void GraphicsEngine::draw_body_part(mat4 MVP) {
    draw_body_part(MVP, colors[BLACK]);
}

void GraphicsEngine::draw_body_part(mat4 MVP, vec3 modcolor) {
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint modcolorID = glGetUniformLocation(programID, "modcolor");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform3f(modcolorID, modcolor.x, modcolor.y, modcolor.z);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, cube_location);
    glDrawElements(GL_LINE_STRIP, 16, GL_UNSIGNED_INT, cube_sketch_location);
}


void GraphicsEngine::cleanup() {
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
}

double GraphicsEngine::checkDeltaTime() {
    current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;
    return delta_time;
}

void GraphicsEngine::drawing_begin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
}

void GraphicsEngine::drawing_end() {
    glfwSwapBuffers();
}

bool GraphicsEngine::is_view_changed() {
    static bool v_pressed;

    if (!v_pressed && (glfwGetKey(GLFW_KEY_V) == GLFW_PRESS)) {
        current_view++;
        current_view %= 4;
        v_pressed = true;
        return true;
    }

    if (v_pressed && (glfwGetKey(GLFW_KEY_V) == GLFW_RELEASE)) {
        v_pressed = false;
    }

    return false;
}
