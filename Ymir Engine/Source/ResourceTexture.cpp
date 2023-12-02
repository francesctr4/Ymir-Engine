#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(uint UID) : Resource(UID, ResourceType::TEXTURE)
{

}

bool ResourceTexture::IsLoadedInMemory()
{
    return false;
}

bool ResourceTexture::LoadInMemory()
{
    return false;
}

bool ResourceTexture::UnloadFromMemory()
{
    return false;
}
