#include "ImporterMesh.h"

void ImporterMesh::Import(const aiMesh* mesh, Mesh* ourMesh)
{

}

uint ImporterMesh::Save(const Mesh* ourMesh, char** fileBuffer)
{
    //uint bufferSize = sizeof(uint) * 5 + sizeof(uint) * ourMesh->num_indices + sizeof(Vertex) * ourMesh->num_vertices;

    //// Asignar dinámicamente el búfer de archivos
    //*fileBuffer = new char[bufferSize];

    //// Utilizar un puntero para rastrear la posición actual en el búfer de archivos
    //char* cursor = *fileBuffer;

    //// Guardar la cantidad de índices, vértices y otros datos en ranges
    //uint ranges[5] = { ourMesh->num_indices, ourMesh->num_vertices, 0, 0, 0 }; // Asumiendo que las otras propiedades son cero por ahora
    //bytes = sizeof(ranges);
    //memcpy(cursor, ranges, bytes);
    //cursor += bytes;

    //// Guardar los índices en el búfer
    //bytes = sizeof(uint) * ourMesh->num_indices;
    //memcpy(cursor, ourMesh->indices, bytes);
    //cursor += bytes;

    //// Guardar los vértices en el búfer
    //bytes = sizeof(Vertex) * ourMesh->num_vertices;
    //memcpy(cursor, ourMesh->vertices, bytes);

    //// Devolver el tamaño del búfer
    //return bufferSize;
}

void ImporterMesh::Load(const char* fileBuffer, Mesh* ourMesh)
{

}
