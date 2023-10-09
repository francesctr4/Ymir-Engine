#include "Model.h"
#include "Log.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcessPreset_TargetRealtime_MaxQuality)

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
	std::vector<GLfloat> vertices;
	std::vector<uint> indices;

	// Process vertices

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		LOG("Vertex read");

		// Process vertex positions

		// Process vertex normals

		/* TODO */

		// Process vertex texture coordinates

		/* TODO */
			
		aiVector3D& pos = mesh->mVertices[i];
		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);
	}

	// Process indices

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		LOG("Index read");
		aiFace face = mesh->mFaces[i];

		for (uint j = 0; j < face.mNumIndices; j++) 
		{
			indices.push_back(face.mIndices[j]);
		}

	}
	
	// Process materials

	/* TODO */

	return Mesh(vertices,indices); // Retrieve the Mesh with all the necessary data to draw
}
