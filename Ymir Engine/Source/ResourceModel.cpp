#include "ResourceModel.h"

ResourceModel::ResourceModel(uint UID) : Resource(UID, ResourceType::MODEL)
{

}

bool ResourceModel::IsLoadedInMemory()
{
    return false;
}

bool ResourceModel::LoadInMemory()
{
    return false;
}

bool ResourceModel::UnloadFromMemory()
{
    return false;
}
