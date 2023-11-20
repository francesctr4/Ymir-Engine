#include "ImporterMesh.h"

void ImporterMesh::Import(const aiMesh* mesh, Mesh* ourMesh)
{

}

uint ImporterMesh::Save(const Mesh* ourMesh, char** fileBuffer)
{
    //uint bufferSize = sizeof(uint) * 5 + sizeof(uint) * ourMesh->num_index + sizeof(Vertex) * ourMesh->num_vertex;

    //// Dynamically allocate file buffer
    //*fileBuffer = new char[bufferSize];

    ////Use a pointer to track the current position in the file buffer
    //char* cursor = *fileBuffer;
    //uint bytes;

    ////Save the number of indexes, vertices and other data in ranges
    //uint ranges[5] = { ourMesh->num_index, ourMesh->num_vertex, 0, 0, 0 };
    //bytes = sizeof(ranges);
    //memcpy(cursor, ranges, bytes);
    //cursor += bytes;

    //// Save index on buffer
    //bytes = sizeof(uint) * ourMesh->num_index;
    //memcpy(cursor, ourMesh->index, bytes);
    //cursor += bytes;

    //// Save vertex on buffer
    //bytes = sizeof(Vertex) * ourMesh->num_vertex;
    //memcpy(cursor, ourMesh->vertex, bytes);

    //// Return size of buffer
    //return bufferSize;
    return uint();
}

void ImporterMesh::Load(const char* fileBuffer, Mesh* ourMesh)
{
    //const char* cursor = fileBuffer;
    //uint bytes;

    //uint ranges[5];
    //uint bytes = sizeof(ranges);
    //memcpy(ranges, cursor, bytes);
    //cursor += bytes;

    //// OurMesh with index vertex plus normals texture etc
    //ourMesh->num_index = ranges[0];
    //ourMesh->num_vertex = ranges[1];

    //// Load index on mesh
    //bytes = sizeof(uint) * ourMesh->num_index;
    //ourMesh->index = new uint[ourMesh->num_index];
    //memcpy(ourMesh->index, cursor, bytes);
    //cursor += bytes;

    //// Load vertex on mesh
    //bytes = sizeof(Vertex) * ourMesh->num_vertex;
    //ourMesh->vertex = new Vertex[ourMesh->num_vertex];
    //memcpy(ourMesh->vertex, cursor, bytes);
}
