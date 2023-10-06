#include "AssetImporter3D.h"

void AssetImporter3D::EnableAssimpDebugger()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
}

void AssetImporter3D::CleanUpAssimpDebugger()
{
	aiDetachAllLogStreams();
}