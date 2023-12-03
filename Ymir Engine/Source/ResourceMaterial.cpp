#include "ResourceMaterial.h"

#include "ResourceShader.h"
#include "ResourceTexture.h"

ResourceMaterial::ResourceMaterial(uint UID) : Resource(UID, ResourceType::MATERIAL)
{
    // Material Shader

    materialShader = std::make_shared<ResourceShader>(0);

    // Material Maps

    materialMaps[MaterialMapType::ALBEDO] = std::make_shared<ResourceTexture>(0);      // Diffuse Texture Type
    materialMaps[MaterialMapType::METALLIC] = std::make_shared<ResourceTexture>(0);    // Specular Texture Type
    materialMaps[MaterialMapType::NORMAL] = std::make_shared<ResourceTexture>(0);      // Normals Texture Type
    materialMaps[MaterialMapType::HEIGHT] = std::make_shared<ResourceTexture>(0);      // Height Texture Type
    materialMaps[MaterialMapType::OCCLUSION] = std::make_shared<ResourceTexture>(0);   // Ambient Texture Type
    materialMaps[MaterialMapType::EMISSION] = std::make_shared<ResourceTexture>(0);    // Emissive Texture Type
}

ResourceMaterial::~ResourceMaterial()
{

}

bool ResourceMaterial::IsLoadedInMemory()
{
    return false;
}

bool ResourceMaterial::LoadInMemory()
{
    return false;
}

bool ResourceMaterial::UnloadFromMemory()
{
    return false;
}

void ResourceMaterial::SetMaterialShader(std::shared_ptr<ResourceShader> newMaterialShader)
{
    materialShader = newMaterialShader;
}

std::shared_ptr<ResourceShader> ResourceMaterial::GetMaterialShader()
{
    return materialShader;
}

std::map<MaterialMapType, std::shared_ptr<ResourceTexture>> ResourceMaterial::GetAllMaterialMaps()
{
    return materialMaps;
}

std::string ResourceMaterial::MaterialMapTypeToString(MaterialMapType mapType)
{
    return materialMapTypeToString.at(mapType);
}

MaterialMapType ResourceMaterial::StringToMaterialMapType(std::string mapName)
{
    MaterialMapType tmpType = MaterialMapType::UNKNOWN;

    for (const auto& pair : materialMapTypeToString) {

        if (pair.second == mapName) {

            tmpType = pair.first;

        }

    }

    return tmpType;
}

void ResourceMaterial::SetMaterialMap(MaterialMapType mapType, std::shared_ptr<ResourceTexture> texture)
{
    materialMaps[mapType] = texture;
}

std::shared_ptr<ResourceTexture> ResourceMaterial::GetMaterialMap(MaterialMapType mapType)
{
    return materialMaps[mapType];
}
