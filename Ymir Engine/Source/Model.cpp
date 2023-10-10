#include "Model.h"
#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

Model::Model()
{

}

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
	const aiScene* scene = aiImportFile(path.c_str(), ASSIMP_LOAD_FLAGS);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		directory = path.substr(0, path.find_last_of('/'));
		ProcessNode(scene->mRootNode, scene);
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path.c_str());
	}

	size_t lastSlashPos = path.find_last_of('/');
	std::string name = path.substr(lastSlashPos + 1);

	LOG("Model created: %s", name.c_str());

}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	// Then do the same for each of its children
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Process vertices

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		float3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;
		// normals
		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		// textures
		if (mesh->mTextureCoords[0]) // Check if the mesh contains texture coordinates
		{
			float2 tempTextureCoords;

			tempTextureCoords.x = mesh->mTextureCoords[0][i].x;
			tempTextureCoords.y = mesh->mTextureCoords[0][i].y;

			vertex.textureCoordinates = tempTextureCoords;
		}
		else
		{
			vertex.textureCoordinates = float2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// Process indices

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (uint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}

	}

	// Process textures

	return Mesh(vertices, indices, textures); // Retrieve the Mesh with all the necessary data to draw
}