#include <iostream>
#include "texture.hpp"

Texture::Texture(GLenum TextureTarget, const std::string& FileName) {
    m_textureTarget = TextureTarget;
    m_fileName      = FileName;
//    m_pImage        = NULL;
}

bool Texture::Load() {
//    try {
//        m_pImage = new Magick::Image(m_fileName);
//        m_pImage->write(&m_blob, "RGBA");
//    }
//    catch (Magick::Error& Error) {
//        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
//        return false;
//    }

//    glGenTextures(1, &m_textureObj);
//    glBindTexture(m_textureTarget, m_textureObj);
//    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
//    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    return true;


    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);

    // Read the file, call glTexImage2D with the right parameters
    if (glfwLoadTexture2D(m_fileName.c_str(), 0) != GL_TRUE) {
        std::cout << "Error loading texture '" << m_fileName << std::endl;
        return false;
    }

    // Nice trilinear filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

void Texture::Bind(GLenum TextureUnit) {
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}
