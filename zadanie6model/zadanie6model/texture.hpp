#ifndef TEXTURE_HPP
#define	TEXTURE_HPP

#include <string>

#include <GL/glew.h>
#include <GL/glfw.h>

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
};


#endif

