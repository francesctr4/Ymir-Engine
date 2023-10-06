#pragma once

#include <string>

#include "External/Assimp/include/Importer.hpp"
#include "External/Assimp/include/cimport.h"
#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/postprocess.h"

#include "Mesh.h"

class Model {

public:

    Model(const std::string& path);
    virtual ~Model();

    void DrawModel();

private:
    
    void LoadModel(const std::string& path);

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    uint TextureFromFile(const std::string& path, const std::string& directory, bool gamma = false);

    // Model Data

    std::vector<Mesh> meshes;
    std::string directory;

    // Vector of already loaded textures

    std::vector<Texture> loadedTextures;

};