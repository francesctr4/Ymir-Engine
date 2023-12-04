#include "ResourceShader.h"

ResourceShader::ResourceShader(uint UID) : Resource(UID, ResourceType::SHADER)
{

}

bool ResourceShader::LoadInMemory()
{
    return false;
}

bool ResourceShader::UnloadFromMemory()
{
    return false;
}
