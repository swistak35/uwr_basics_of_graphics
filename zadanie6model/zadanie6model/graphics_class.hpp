#ifndef GRAPHICS_CLASS_HPP
#define GRAPHICS_CLASS_HPP

#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "utils.hpp"
#include "model.hpp"

using namespace glm;

class GraphicsEngine {
public:
    // General OpenGL attributes
    GLuint VertexArrayID;
    GLuint programID;
    GLuint mvpID, mod_colorID, textureID;
    GLuint colorProgramID, textureProgramID, woodProgramID, dirtProgramID;
    GLuint vertexShader, colorShader, textureShader, woodShader, dirtShader;
    GLuint vertexbuffer, elementbuffer;
    static constexpr int window_width = 1000;
    static constexpr int window_height = 700;
    static constexpr GLfloat window_ratio = float(window_width) / window_height;
    std::vector<vtx> vertices;
    std::vector<unsigned int> indices;
    mat4 VP;

    // Time and fps measuring
    double current_time;
    double last_time;
    double delta_time;
    double render_time;
    int frames_count = 0;
    double last_fps_print = 0.0;


    Model * model_plane;
    Model * model_wall;
    Model * model3;
    void * model_location;
    int model_amount;
    void initMesh(unsigned int Index, const aiMesh* paiMesh);

    // API
    GraphicsEngine();
    void send_buffers();
    void input_service();
    mat4 getMVP();
    bool close_window_condition();
    void cleanup();
    double checkDeltaTime();
    void drawing_begin();
    void drawing_end();


    // Other
    int status;
private:
    int initialize_opengl();
    void initialize_buffers();
    void initialize_model();
};


#endif
