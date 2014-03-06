#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint LoadVertexShader(const char * vertex_file_path);
GLuint LoadFragmentShader(const char * fragment_file_path);
GLuint LoadProgram(GLuint VertexShaderID, GLuint FragmentShaderID);
#endif
