#pragma once

#include <string>
#include "Globals.h"

enum class ResourceType {

	UNKNOWN,
	TEXTURE,
	MESH,
	MODEL,
	SCENE,
	SHADER,
	MATERIAL,

};

class Resource {
public:

	Resource();
	Resource(uint UID, ResourceType type);
	virtual ~Resource();

	ResourceType GetType() const;
	uint GetUID() const;

	void SetAssetsFilePath(const std::string& newPath);
	void SetLibraryFilePath(const std::string& newPath);

	std::string GetAssetsFilePath() const;
	std::string GetLibraryFilePath() const;

	uint GetReferenceCount() const;
	void IncreaseReferenceCount();
	void DecreaseReferenceCount();

	virtual bool IsLoadedInMemory() = 0;
	virtual bool LoadInMemory() = 0;
	virtual bool UnloadFromMemory() = 0;

protected:

	std::string assetsFilePath;
	std::string libraryFilePath;

	ResourceType type;
	uint UID;

	uint referenceCount;

};