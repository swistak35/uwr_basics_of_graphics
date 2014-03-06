#ifndef MODEL_HPP
#define	MODEL_HPP

// #include <map>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "utils.hpp"
#include "texture.hpp"


class Model {
public:
    Model();
    ~Model();
    bool LoadModel(GLuint programID, const std::string& Filename);
    void Render(mat4 MVP);

private:
    GLuint programID, mvpID, textureID;
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

    struct MeshEntry {
        MeshEntry();
        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
                  const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;
};


#endif
