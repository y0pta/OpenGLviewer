//
// Created by Liza on 3/12/2023.
//

#include "Mesh.h"
#include <string>

bool MeshEntry::init(unsigned int index, const aiMesh* paiMesh)
{
    materialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        const aiVector3D* pTangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero3D;
        const aiVector3D* pBitangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero3D;

        Vertex v;
        v.position = glm::vec3(pPos->x, pPos->y, pPos->z);
        v.texCoords = glm::vec2(pTexCoord->x, pTexCoord->y);
        v.normal = glm::vec3(pNormal->x, pNormal->y, pNormal->z);
        v.tangent = glm::vec3(pTangent->x, pTangent->y, pTangent->z);
        v.bitangent = glm::vec3(pBitangent->x, pBitangent->y, pBitangent->z);

        vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }
    init(vertices, indices);

    return true;
}

bool MeshEntry::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    numIndices = indices.size();

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);

    // TODO: check errors via gl built-in functions
    return true;
}

void MeshEntry::render() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

Mesh::Mesh(const std::string& loadPath) : shader(Shader::instance(Shader::eMesh)){
    _load(loadPath);
}

bool Mesh::_load(const std::string &loadPath){
    _clear();

    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(loadPath.c_str(),
                                              aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    bool ret = false;
    if (pScene) {
        entries.resize(pScene->mNumMeshes);
        textures.resize(pScene->mNumMaterials);

        // Initialize the meshes in the scene one by one
        for (unsigned int i = 0 ; i < entries.size() ; i++) {
            const aiMesh* paiMesh = pScene->mMeshes[i];
            entries[i].init(i, paiMesh);
        }

        ret = _initMaterials(pScene, loadPath);
    }
    else {
        std::cout << "Error parsing " << loadPath <<  " " << importer.GetErrorString() << std::endl;
    }

    return ret;
}

bool Mesh::
_initMaterials(const aiScene* pScene, const std::string& loadPath)
{
    // Extract the directory part from the file name
    std::string::size_type slashIndex = loadPath.find_last_of("/");
    std::string dir;

    if (slashIndex == std::string::npos) {
        dir = ".";
    }
    else if (slashIndex == 0) {
        dir = "/";
    }
    else {
        dir = loadPath.substr(0, slashIndex);
    }

    bool ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string p(Path.data);

                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }

                std::string fullPath = dir + "/" + p;

                textures[i] = Texture(fullPath);

                if (!textures[i].isInitialized()) {
                    std::cout <<"Error loading texture " << fullPath << std::endl;
                    ret = false;
                }
                else {
                    std::cout <<"Loaded texture " << fullPath << std::endl;
                }
            }
        }
    }

    return ret;
}

/*
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures): shader(Shader::instance(Shader::eMesh))
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}*/

void Mesh::render(Camera* cam)
{
    shader.use();
    shader.setMat4("model", glm::mat4(1.0f));
    shader.setMat4("view", cam->getViewMatrix());
    shader.setMat4("projection", cam->getProjectionMatrix());
    for (auto& mesh : entries){
        mesh.render();
    }
}

void Mesh::_clear() {
    // TODO: think about safe delete of resources
}