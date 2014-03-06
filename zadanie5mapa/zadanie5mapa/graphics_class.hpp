#ifndef GRAPHICS_CLASS_HPP
#define GRAPHICS_CLASS_HPP

#include <vector>
#include <glm/glm.hpp>
#include "utils.hpp"

using namespace glm;

class GraphicsEngine {
public:
    // General OpenGL attributes
    GLuint VertexArrayID;
    GLuint programID;
    GLuint mvpID, mod_colorID;
    GLuint vertexbuffer, elementbuffer;
    static constexpr int window_width = 1000;
    static constexpr int window_height = 700;
    static constexpr GLfloat window_ratio = float(window_width) / window_height;
    std::vector<vtx> vertices;
//    std::vector<unsigned int> indices_points[LODS];
    std::vector<unsigned int> indices_triangles[LODS];
    std::vector<unsigned int> indices_globe;
    int lod;
    mat4 VP;
    bool auto_mode = false;

    // Time and fps measuring
    double current_time;
    double last_time;
    double delta_time;
    double render_time;
    int frames_count = 0;
    int current_mode;
    double last_fps_print = 0.0;

    // API
    GraphicsEngine(int mode);
    void send_buffers();
    void update_lod(int l);
    void input_service();
    mat4 getMVP();
    bool close_window_condition();
    void cleanup();
    double checkDeltaTime();
    void drawing_begin();
    void drawing_end();
    void drawMap();


    // Other
    int status;
private:
    int initialize_opengl();
    void initialize_buffers();
    void initialize_globe();
};


#endif
