#pragma once

#include <memory>
#include <map>
#include <string>

#include "Resources.h"

class ResourceShader;
class ResourceTexture;

enum class MaterialMapType {

	UNKNOWN = -1, // NULL Type

	ALBEDO,		// Diffuse Texture Type
	METALLIC,	// Specular Texture Type
	NORMAL,		// Normal Texture Type
	HEIGHT,		// Height Texture Type
	OCCLUSION,  // Ambient Texture Type
	EMISSION,	// Emissive Texture Type

	NUM_TYPES	// Total Quantity of Types

};

class ResourceMaterial : public Resource {
public:

	// Constructor & Destructor
	
	ResourceMaterial(uint UID);
	virtual ~ResourceMaterial();

	// Inherited Functions

	bool LoadInMemory() override;
	bool UnloadFromMemory() override;

	// Specific Functions

	void SetMaterialShader(std::shared_ptr<ResourceShader> newMaterialShader);
	std::shared_ptr<ResourceShader> GetMaterialShader();

	void SetMaterialMap(MaterialMapType mapType, std::shared_ptr<ResourceTexture> texture);
	std::shared_ptr<ResourceTexture> GetMaterialMap(MaterialMapType mapType);
	std::map<MaterialMapType, std::shared_ptr<ResourceTexture>> GetAllMaterialMaps();

	std::string MaterialMapTypeToString(MaterialMapType mapType);
	MaterialMapType StringToMaterialMapType(std::string mapName);

public:

	static ResourceMaterial* defaultMaterial;

private:

	// Material Shader

	std::shared_ptr<ResourceShader> materialShader;

	// Material Maps

	std::map<MaterialMapType, std::shared_ptr<ResourceTexture>> materialMaps;

	// Utility Map

	std::map<MaterialMapType, std::string> materialMapTypeToString {

		{MaterialMapType::ALBEDO, "Albedo"},
		{MaterialMapType::METALLIC, "Metallic"},
		{MaterialMapType::NORMAL, "Normal"},
		{MaterialMapType::HEIGHT, "Height"},
		{MaterialMapType::OCCLUSION, "Occlusion"},
		{MaterialMapType::EMISSION, "Emission"},

	};

};