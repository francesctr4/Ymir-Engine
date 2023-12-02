#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(uint UID) : Resource(UID, ResourceType::MESH)
{

}

bool ResourceMesh::IsLoadedInMemory()
{
    return false;
}

bool ResourceMesh::LoadInMemory()
{
    return false;
}

bool ResourceMesh::UnloadFromMemory()
{
    return false;
}