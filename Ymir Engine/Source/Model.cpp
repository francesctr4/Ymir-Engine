#include "Model.h"
#include "Log.h"

Model::Model(const std::string& path)
{
	LoadModel(path);
}

Model::~Model()
{

}

void Model::DrawModel()
{
	for (auto it = meshes.begin(); it != meshes.end(); ++it) {

		(*it).DrawMesh();

	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG("ERROR::ASSIMP::", importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{

}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{

	return;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{

	return;
}
