#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"

#include "graphics_class.hpp"

using namespace glm;

void GraphicsEngine::initialize_buffers() {
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
}

GraphicsEngine::GraphicsEngine(int mode) {
    current_mode = mode;
    status = initialize_opengl();
    if (current_mode == 3) {
        initialize_globe();
    }
    initialize_buffers();

    last_time = glfwGetTime();
    last_fps_print = last_time;
}

void GraphicsEngine::initialize_globe() {
    for(int lat = 0; lat < 180; lat++) {
        for(int lng = 0; lng < 360; lng++) {
            vertices.push_back({
                GLfloat(lng),
                GLfloat(lat),
                0.0
            });
            indices_globe.push_back(vertices.size() - 1);
        }
    }
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

    glfwSetWindowTitle("Mapa");

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
    if (current_mode == 3) {
        programID = LoadShaders( "VertexShader3D.vert", "ColorFragmentShader.frag" );
    } else {
        programID = LoadShaders( "VertexShader2D.vert", "ColorFragmentShader.frag" );
    }

    glfwSetMousePos(1000/2, 700/2);
    return 0;
}

void GraphicsEngine::update_lod(int lod) {
    this->lod = lod;
    std::cout << "Level of detail changed to " << lod << ".\n";
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (indices_triangles[lod].size() + indices_globe.size()) * sizeof(unsigned int), &indices_triangles[lod][0], GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indices_triangles[lod].size() * sizeof(unsigned int), indices_globe.size() * sizeof(unsigned int), &indices_globe[0]);
}

void GraphicsEngine::send_buffers() {
    glUseProgram(programID);

    mvpID = glGetUniformLocation(programID, "MVP");
    mod_colorID = glGetUniformLocation(programID, "mod_color");

    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        sizeof(vtx),        // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
        1,                  // size
        GL_FLOAT,             // type
        GL_FALSE,           // normalized?
        sizeof(vtx),        // stride
        (void*)(2*sizeof(GLfloat))            // array buffer offset
    );

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vtx), &vertices[0], GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_points[lod].size() * sizeof(unsigned int), &indices_points[lod][0], GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_triangles[lod].size() * sizeof(unsigned int), &indices_triangles[lod][0], GL_STATIC_DRAW);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_globe.size() * sizeof(unsigned int), &indices_globe[0], GL_STATIC_DRAW);
}

bool GraphicsEngine::close_window_condition() {
    return (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
            glfwGetWindowParam(GLFW_OPENED));
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
    frames_count++;
    delta_time = current_time - last_time;
    last_time = current_time;

    if (current_time - last_fps_print >= 1.0) {
        std::cout << 1000.0/double(frames_count) << " ms/frame;\t" << frames_count << " fps\n";
        last_fps_print = current_time;

        if (auto_mode) {
            if (lod > 0 && frames_count > 45) {
                update_lod(lod-1);
                std::cout << "dupa tam\n";
            }
            if (lod < LODS-1 && frames_count < 10) {
                update_lod(lod+1);
                std::cout << "dupa tu\n";
            }
        }
        frames_count = 0;
    }

    return delta_time;
}

void GraphicsEngine::drawing_begin() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
}

void GraphicsEngine::drawing_end() {
    glfwSwapBuffers();
}

mat4 GraphicsEngine::getMVP() {
    return (VP * mat4(1.0f));
}

void GraphicsEngine::drawMap() {
    mat4 MVP = getMVP();

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
    if (current_mode == 3) {
        glUniform3f(mod_colorID, 1.0, 1.0, 1.0);
        glDrawElements(GL_POINTS, indices_globe.size() * 50, GL_UNSIGNED_INT, (void*)(indices_triangles[lod].size() * sizeof(unsigned int)));
        glUniform3f(mod_colorID, 0.0, 0.0, 0.0);
//        std::cout << indices_globe.size() << std::endl;
    }
//    glDrawElements(GL_POINTS, indices_points[lod].size(), GL_UNSIGNED_INT, (void*) 0);
    glDrawElements(GL_TRIANGLES, indices_triangles[lod].size(), GL_UNSIGNED_INT, (void*) 0);
}

void GraphicsEngine::input_service() {
    static bool num_pressed[10] = { false };

    for (int i = 1; i < 10; i++) {
        if (!num_pressed[i] && (glfwGetKey(numkeys[i]) == GLFW_PRESS)) {
            auto_mode = false;
            update_lod(i-1);
            num_pressed[i] = true;
        }

        if (num_pressed[i] && (glfwGetKey(numkeys[i]) == GLFW_RELEASE)) {
            num_pressed[i] = false;
        }
    }

    if (!num_pressed[0] && (glfwGetKey(numkeys[0]) == GLFW_PRESS)) {
        auto_mode = true;
        num_pressed[0] = true;
    }

    if (num_pressed[0] && (glfwGetKey(numkeys[0]) == GLFW_RELEASE)) {
        num_pressed[0] = false;
    }
}
