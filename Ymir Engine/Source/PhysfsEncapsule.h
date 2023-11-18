#pragma once

#include <cstddef>
#include <string>
#include <filesystem>

#include "External/PhysFS/include/physfs.h"
#pragma comment (lib, "Source/External/PhysFS/libx86/physfs.lib")

namespace PhysfsEncapsule {

    void InitializePhysFS();
    bool FolderExists(std::string route);
    void CreateFolder(std::string route, std::string folderName);
    void ReadFolder(std::string route);
    void DeleteFolder(std::string route);
    bool CopyFileFromSource(std::string source, std::string destination);
    void DeinitializePhysFS();

}