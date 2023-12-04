#include "ResourceScene.h"

ResourceScene::ResourceScene(uint UID) : Resource(UID, ResourceType::SCENE)
{

}

bool ResourceScene::LoadInMemory()
{
    return false;
}

bool ResourceScene::UnloadFromMemory()
{
    return false;
}
