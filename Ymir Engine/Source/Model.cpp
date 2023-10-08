#include "Model.h"
#include "Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

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
	const aiScene* scene = importer.ReadFile(path, ASSIMP_LOAD_FLAGS);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG("ERROR::ASSIMP:: %s", importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
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
	std::vector<uint> indices;
	std::vector<Texture> textures;

	// Process vertices

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		LOG("Vertex read");
		Vertex vertex;

		// Process vertex positions

		float3 tempPosition;

		tempPosition.x = mesh->mVertices[i].x;
		tempPosition.y = mesh->mVertices[i].y;
		tempPosition.z = mesh->mVertices[i].z;

		vertex.position = tempPosition;

		// Process vertex normals

		float3 tempNormal;

		tempNormal.x = mesh->mNormals[i].x;
		tempNormal.y = mesh->mNormals[i].y;
		tempNormal.z = mesh->mNormals[i].z;

		vertex.normal = tempNormal;

		// Process vertex texture coordinates

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
			
		vertices.push_back(vertex); // Push the vertex to our vector of vertices with all the info retrieved
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

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures); // Retrieve the Mesh with all the necessary data to draw
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;

		for (auto it = loadedTextures.begin(); it != loadedTextures.end(); ++it)
		{
			if (std::strcmp((*it).path.data(), str.C_Str()) == 0) // If the texture already exists, don't load it again
			{
				textures.push_back((*it));

				skip = true;
				break;
			}
		}

		if (!skip) // If the texture is new, load it
		{
			Texture texture;

			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();

			textures.push_back(texture);
			loadedTextures.push_back(texture); // Save texture to keep track that we already loaded it
		}
		
	}

	return textures;
}

uint Model::TextureFromFile(const std::string& path, const std::string& directory, bool gamma)
{
	std::string filename = path;
	filename = directory + '/' + filename;

	uint textureID;
	glGenTextures(1, &textureID);

	int width;
	int height;
	int nrComponents;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;

		if (nrComponents == 1) {

			format = GL_RED;

		}
		else if (nrComponents == 3) {

			format = GL_RGB;

		}
		else if (nrComponents == 4) {

			format = GL_RGBA;

		}
		
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		LOG("Texture failed to load at path: %s", path);
		stbi_image_free(data);
	}

	return textureID;
}
