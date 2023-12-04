#include "ImporterMesh.h"

void ImporterMesh::Import(const aiMesh* mesh, Mesh* ourMesh)
{

}

uint ImporterMesh::Save(const Mesh* ourMesh, char** fileBuffer)
{
    // Define the size of the header (ranges) and data (vertices)
    uint headerSize = sizeof(uint) * 2; // num_indices and num_vertices
    uint vertexSize = sizeof(float) * 3 + sizeof(float) * 3 + sizeof(float) * 2; // size of Vertex structure

    // Calculate the total size of the file buffer
    uint size = headerSize + sizeof(uint) * ourMesh->indices.size() + vertexSize * ourMesh->vertices.size();

    // Allocate memory for the file buffer
    *fileBuffer = new char[size];

    // Create a cursor to keep track of the current position in the buffer
    char* cursor = *fileBuffer;

    // Store the header (ranges)
    uint ranges[2] = { ourMesh->indices.size(), ourMesh->vertices.size() };
    uint bytes = headerSize;
    memcpy(cursor, ranges, bytes);
    cursor += bytes;

    // Store the indices
    bytes = sizeof(uint) * ourMesh->indices.size();
    memcpy(cursor, ourMesh->indices.data(), bytes);
    cursor += bytes;

    // Store the vertices
    bytes = sizeof(float) * 3 * ourMesh->vertices.size() + sizeof(float) * 3 * ourMesh->vertices.size() + sizeof(float) * 2 * ourMesh->vertices.size();
    memcpy(cursor, ourMesh->vertices.data(), bytes);
    cursor += bytes;

    // Return the size of the file buffer
    return size;
}

void ImporterMesh::Load(const char* fileBuffer, ResourceMesh* ourMesh)
{
    char* cursor = const_cast<char*>(fileBuffer);

    // Load the header (ranges)
    uint ranges[2];
    uint bytes = sizeof(ranges);
    memcpy(ranges, cursor, bytes);
    cursor += bytes;

    // Resize indices and vertices
    ourMesh->indices.resize(ranges[0]);
    ourMesh->vertices.resize(ranges[1]);

    // Load indices
    bytes = sizeof(uint) * ourMesh->indices.size();
    memcpy(ourMesh->indices.data(), cursor, bytes);
    cursor += bytes;

    // Load vertices
    bytes = sizeof(float) * 3 * ourMesh->vertices.size() + sizeof(float) * 3 * ourMesh->vertices.size() + sizeof(float) * 2 * ourMesh->vertices.size();
    memcpy(ourMesh->vertices.data(), cursor, bytes);
    cursor += bytes;
}
