#ifndef UTILS_HPP
#define UTILS_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#define DEBUG               true
#define ANGLES 0.017453292519943295
#define FOR(q,n) for(int q=0;q<n;q++)
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#define INVALID_OGL_VALUE   0xFFFFFFFF
#define INVALID_MATERIAL    0xFFFFFFFF

using namespace glm;

//typedef struct VertexStruct {
//    GLfloat x,y,z;
//} vtx;

typedef struct Vertex
{
    GLfloat m_pos_x, m_pos_y, m_pos_z;
    GLfloat m_tex_x, m_tex_y;
    GLfloat m_normal_x, m_normal_y, m_normal_z;
//    vec3 m_pos;
//    vec2 m_tex;
//    vec3 m_normal;

//    Vertex() {}

//    Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
//    {
//        m_pos    = pos;
//        m_tex    = tex;
//        m_normal = normal;
//    }
} vtx;


extern int numkeys[10];

#endif
