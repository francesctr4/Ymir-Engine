#pragma once

#include <string>

#include "Mesh.h"

#include "External/Assimp/include/cimport.h"
#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/postprocess.h"

#pragma comment (lib, "Source/External/Assimp/libx86/assimp.lib")

class Model {

public:

    Model();
    Model(const std::string& path);

    virtual ~Model();

    void LoadModel(const std::string& path);
    void DrawModel();

private:

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

public:

    // Model Data

    std::string name;

    std::vector<Mesh> meshes;
    std::string directory;

};