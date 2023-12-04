#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(uint UID) : Resource(UID, ResourceType::TEXTURE)
{

}

bool ResourceTexture::LoadInMemory()
{
    return false;
}

bool ResourceTexture::UnloadFromMemory()
{
    return false;
}
