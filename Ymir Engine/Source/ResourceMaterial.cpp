#include "ResourceMaterial.h"

ResourceMaterial::ResourceMaterial(uint UID) : Resource(UID, ResourceType::MATERIAL)
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
