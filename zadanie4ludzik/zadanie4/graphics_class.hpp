#ifndef GRAPHICS_CLASS_HPP
#define GRAPHICS_CLASS_HPP

#include <glm/glm.hpp>

using namespace glm;

class Person;

typedef struct VertexStruct {
    GLfloat x,y,z,r,g,b;
} vtx;

enum Color { YELLOW, WHITE, BLACK, BROWN, RED, GREEN, BLUE, CYAN, MAGENTA };

class GraphicsEngine {
public:
    // General OpenGL attributes
    GLuint VertexArrayID;
    GLuint programID;
    GLuint vertexbuffer, elementbuffer;
    static constexpr int window_width = 1000;
    static constexpr int window_height = 700;
    static constexpr GLfloat window_ratio = float(window_width) / window_height;
    std::vector<vtx> vertices;
    std::vector<unsigned int> indices;
    double current_time;
    double last_time;
    double delta_time;
    int current_view;
    Person * observer;
    vec3 colors[9];

    //Below will go to logic later
    double pox_x, pos_y, pos_z;

    // Cube object info
    const void * cube_location;
    const void * cube_sketch_location;

    // API
    GraphicsEngine();
    void send_buffers();
    void draw_cube();
    mat4 getMVP();
    mat4 getMovingVP();
    mat4 getUpVP();
    mat4 get1PersonVP();
    mat4 get3PersonVP();
    void draw_body_part(mat4 Init);
    void draw_body_part(mat4 Init, vec3 modcolor);
    bool close_window_condition();
    void cleanup();
    double checkDeltaTime();
    void drawing_begin();
    void drawing_end();
    bool is_view_changed();

    // Other
    int status;
private:
    int initialize_opengl();
    void initialize_buffers();
    void initialize_cube_data();
};


#endif
