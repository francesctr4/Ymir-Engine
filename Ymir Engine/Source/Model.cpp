#include "Model.h"
#include "Log.h"

#include "GameObject.h"
#include "ModuleScene.h"

#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcessPreset_TargetRealtime_MaxQuality)

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
	if (modelGO->active && External->scene->mRootNode->active) {

		for (auto it = meshes.begin(); it != meshes.end(); ++it) {

			if ((*it).meshGO->active) {

				(*it).DrawMesh();

			}
			
		}

	}
	
}

void Model::LoadModel(const std::string& path)
{
	// Retrieve info about Model (directory and name)

	if (path.find('\\') != std::string::npos) {

		directory = path.substr(0, path.find_last_of('\\') + 1);

	}
	else {

		directory = path.substr(0, path.find_last_of('/') + 1);

	}

	size_t lastDot = path.find_last_of('.');

	if (path.find("/") != std::string::npos) {

		size_t lastSlash = path.find_last_of('/') + 1;
		name = path.substr(lastSlash, lastDot - lastSlash);

	}
	else {

		size_t lastSlash = path.find_last_of('\\') + 1;
		name = path.substr(lastSlash, lastDot - lastSlash);

	}

	// Import the model using Assimp

	const aiScene* scene = aiImportFile(path.c_str(), ASSIMP_LOAD_FLAGS);

	if (scene != nullptr && scene->HasMeshes())
	{
		ProcessNode(scene->mRootNode, scene, nullptr);

		LOG("Model created: %s", name.c_str());

		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path.c_str());
	}

}

void Model::ProcessNode(aiNode* node, const aiScene* scene, GameObject* parentGO)
{
	GameObject* currentNodeGO;

	if (parentGO == nullptr) {
		// If the current node is the root node, create here the model GameObject, parented to scene GameObject
		currentNodeGO = External->scene->CreateGameObject(name, External->scene->mRootNode);
		modelGO = currentNodeGO;
	}
	else {
		// Create a GameObject for the current node and set it as a child of the parent GameObject
		currentNodeGO = External->scene->CreateGameObject(node->mName.C_Str(), parentGO);
		
	}

	aiVector3D translation, scaling;
	aiQuaternion rotation;

	node->mTransformation.Decompose(scaling, rotation, translation);

	NodeTransform tmpNodeTransform;

	tmpNodeTransform.translation = { translation.x, translation.y, translation.z };

	Quat rotQ(rotation.x, rotation.y, rotation.z, rotation.w);
	tmpNodeTransform.rotation = { rotQ.ToEulerXYZ() };

	tmpNodeTransform.scale = { scaling.x, scaling.y, scaling.z};

	// Process all the node's meshes (if any)

	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		
		meshes.push_back(ProcessMesh(mesh, scene, currentNodeGO, &tmpNodeTransform));
	}

	// Then do the same for each of its children

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, currentNodeGO);
	}
	
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, GameObject* linkGO, NodeTransform* transform)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Process Vertices

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Retrieve vertex positions

		float3 vPosition;

		vPosition.x = mesh->mVertices[i].x;
		vPosition.y = mesh->mVertices[i].y;
		vPosition.z = mesh->mVertices[i].z;

		vertex.position = vPosition;

		// Retrieve vertex normals

		if (mesh->HasNormals())
		{
			float3 vNormals;

			vNormals.x = mesh->mNormals[i].x;
			vNormals.y = mesh->mNormals[i].y;
			vNormals.z = mesh->mNormals[i].z;

			vertex.normal = vNormals;
		}

		// Retrieve vertex texture coordinates

		if (mesh->HasTextureCoords(0))
		{
			float2 vTextureCoords;
			
			vTextureCoords.x = mesh->mTextureCoords[0][i].x;
			vTextureCoords.y = mesh->mTextureCoords[0][i].y;

			vertex.textureCoordinates = vTextureCoords;
		}
		else
		{
			vertex.textureCoordinates = float2(0.0f, 0.0f);
		}

		// Create vertex with all the information stored

		vertices.push_back(vertex);
	}

	// Process Indices

	if (mesh->HasFaces()) {

		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (uint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}

		}

	}

	// Process Textures

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

		if (numTextures > 0) {

			aiString aiPath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath);

			std::string path = directory + aiPath.C_Str();

			Texture tmpTexture;

			tmpTexture.path = path;
			tmpTexture.type = TextureTypes::DIFFUSE;

			textures.push_back(tmpTexture);

		}
		
	}

	CMesh* cmesh = new CMesh(linkGO);

	cmesh->nVertices = vertices.size();
	cmesh->nIndices = indices.size();

	linkGO->AddComponent(cmesh);

	return Mesh(vertices, indices, textures, linkGO, transform); // Retrieve the Mesh with all the necessary data to draw
}