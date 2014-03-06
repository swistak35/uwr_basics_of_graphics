#ifndef GRAPHICS_CLASS_HPP
#define GRAPHICS_CLASS_HPP

#include <glm/glm.hpp>

typedef struct VertexStruct {
    GLfloat x,y,z,r,g,b;
} vtx;

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

    // Brick object info
    const void * brick_location;
    static constexpr GLfloat brick_ext_width = 0.14;
    static constexpr GLfloat brick_ext_height = 0.08;
    static constexpr GLfloat brick_int_width = 0.1;
    static constexpr GLfloat brick_int_height = 0.05;
    GLfloat brick_offset_x;
    static constexpr GLfloat brick_offset_y = 0.03;

    // Ball object info
    const void * ball_location;
    static constexpr GLfloat ball_radius = 0.03;
    static constexpr int ball_precision = 180;

    // Board object info
    const void * board_location;
    static constexpr GLfloat board_width = 0.3f;
    static constexpr GLfloat board_height = 0.05f;
    static constexpr GLfloat board_y_position = -0.8f;

    // Background object info
    const void * bg_location;
    static constexpr GLfloat bg_hex_height = 0.02;

    // API
    GraphicsEngine();
    void send_buffers();
    void draw_bricks(int cols, int rows, bool bricks[]);
    void draw_ball(GLfloat x, GLfloat y);
    void draw_board(GLfloat translation);
    void draw_bg();
    bool close_window_condition();
    void cleanup();
    int is_arrow_pressed();
    double checkDeltaTime();
    void fetch_data(int cols, int rows);
    glm::vec2 get_brick_pos(int col, int row);
    void drawing_begin();
    void drawing_end();

    // Other
    int status;
private:
    int initialize_opengl();
    void initialize_buffers();
    void initialize_brick_data();
    void initialize_ball_data();
    void initialize_board_data();
    void initialize_bg_data();
};


#endif
