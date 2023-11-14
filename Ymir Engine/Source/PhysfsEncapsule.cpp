#include "PhysfsEncapsule.h"

void PhysfsEncapsule::InitializePhysFS()
{
    if (PHYSFS_init(NULL) == 0) {
        // Handle initialization error
    }
}

bool PhysfsEncapsule::FolderExists(std::string route)
{
    return std::filesystem::exists(route);
}

void PhysfsEncapsule::CreateFolder(std::string route, std::string folderName)
{
    // Set the write directory (this is where you can create folders and files)
    if (PHYSFS_setWriteDir(route.c_str()) == 0) {
        // Handle setting write directory error
       
    }

    // Create a folder (directory)
    if (PHYSFS_mkdir(folderName.c_str()) == 0) {
        // Handle folder creation error
        // Note: If the folder already exists, PHYSFS_mkdir will return success.
        // You may want to check if the folder already exists before attempting to create it.
        
    }
}

void PhysfsEncapsule::DeleteFolder(std::string route)
{
    // Iterate over the directory and delete files
    for (const auto& entry : std::filesystem::directory_iterator(route)) {

        if (std::filesystem::is_directory(entry.path())) {
            // Recursively delete subdirectories
            DeleteFolder(entry.path().string());
        }
        else {
            // Delete files
            if (PHYSFS_delete(entry.path().string().c_str()) == 0) {
            }
        }
    }

    // Delete the empty directory
    if (PHYSFS_delete(route.c_str()) == 0) {



    }

    //// Check if the file exists using std::filesystem
    //if (std::filesystem::exists(route)) {
    //    // Use PhysFS to delete the file
    //    if (PHYSFS_delete(route.c_str()) == 0) {
    //        
    //    }
    //  
    //}
  
}

bool PhysfsEncapsule::CopyFileFromSource(std::string source, std::string destination)
{
    PHYSFS_File* srcFile = PHYSFS_openRead(source.c_str());
    if (srcFile == nullptr) {
        
        return false;
    }

    PHYSFS_File* destFile = PHYSFS_openWrite(destination.c_str());
    if (destFile == nullptr) {
        
        PHYSFS_close(srcFile);
        return false;
    }

    const int bufferSize = 4096;
    char buffer[bufferSize];

    PHYSFS_sint64 bytesRead;
    while ((bytesRead = PHYSFS_read(srcFile, buffer, 1, bufferSize)) > 0) {
        PHYSFS_write(destFile, buffer, 1, static_cast<PHYSFS_uint32>(bytesRead));
    }

    PHYSFS_close(srcFile);
    PHYSFS_close(destFile);

    return true;
}

void PhysfsEncapsule::DeinitializePhysFS()
{
    // Deinitialize PhysFS
    PHYSFS_deinit();
}
