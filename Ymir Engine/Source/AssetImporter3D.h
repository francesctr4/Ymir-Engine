#pragma once

#include "External/Assimp/include/cimport.h"
#include "External/Assimp/include/scene.h"
#include "External/Assimp/include/postprocess.h"

#pragma comment (lib, "Source/External/Assimp/libx86/assimp.lib")

namespace AssetImporter3D {

	// Stream Assimp Log messages to Debug window
	void EnableAssimpDebugger();

	// Detach Assimp Log Stream
	void CleanUpAssimpDebugger();

}