#ifndef UTILS_HPP
#define UTILS_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#define DRAW_TRIANGLES      true
#define DEBUG               true
#define GLOBE_CLASS_DEBUG   false
#define STRICTER_LOD        true
#define LODS                9

#define ANGLES 0.017453292519943295

using namespace glm;

typedef struct VertexStruct {
    GLfloat a,b;      // 2d position
    GLfloat h;          // height for 2d position
} vtx;

extern int numkeys[10];

#endif
