//
// Created by Liza on 3/12/2023.
//

#ifndef OPENGL_PRJ_MESH_H
#define OPENGL_PRJ_MESH_H

#include <map>
#include <vector>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 texCoords;
};

struct MeshEntry{
    MeshEntry(){}
    ~MeshEntry(){}

    bool init(const std::vector<Vertex>& vertices,
              const std::vector<unsigned int>& indices);
    bool init(unsigned int Index, const aiMesh* paiMesh);
    void render();

    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int numIndices = 0;
    unsigned int materialIndex = 0;
};

class Mesh {
    public:
        //Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        Mesh(const std::string& loadPath);
        void render(Camera* cam);

    protected:
        bool _load(const std::string& loadPath);
        bool _initMaterials(const aiScene* pScene, const std::string& loadPath);
        void _clear();

    protected:
        std::vector<MeshEntry> entries;
        std::vector<Texture> textures;

        unsigned int VAO;
        unsigned int VBO, EBO;

        Shader& shader;
};


#endif //OPENGL_PRJ_MESH_H
