#include "CMesh.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"
#include "ModuleResourceManager.h"

CMesh::CMesh(GameObject* owner) : Component(owner, ComponentType::MESH)
{
    meshReference = nullptr;
}

CMesh::~CMesh()
{

}

void CMesh::Enable()
{

}

void CMesh::Disable()
{

}

void CMesh::Update()
{

}

void CMesh::OnInspector()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::CollapsingHeader("Mesh", flags))
    {
        ImGui::Indent();

        ImGui::Spacing();

        ImGui::Text("Current .ymesh UID: %d", 0);

        ImGui::Spacing();

        ImGui::Button("Drop .ymesh to change mesh", ImVec2(200, 50));
        YmeshDragDropTarget();

        ImGui::Spacing();

        ImGui::Text("Vertices: %d", nVertices);

        ImGui::Spacing();

        ImGui::Text("Indices: %d", nIndices);

        ImGui::Spacing();

        for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

            for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

                if ((*jt).meshGO->selected || (*it).modelGO->selected) {

                    ImGui::Checkbox("Show Vertex Normals", &(*jt).enableVertexNormals);
                    ImGui::Spacing();

                    ImGui::Checkbox("Show Face Normals", &(*jt).enableFaceNormals);
                    ImGui::Spacing();

                }

            }

        }

        ImGui::Unindent();
    }
}

void CMesh::YmeshDragDropTarget()
{
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ymesh"))
        {
            std::string* libraryFilePathDrop = (std::string*)payload->Data;

            if (meshReference != nullptr) {

                //External->resourceManager->UnloadResource(meshReference->GetUID());

                meshReference = nullptr;

            }

            // Retrieve name of the file dropped, and then get the UID.

            // Lastly, Request Resource of the Mesh with given UID, Path and Type and render it (add a reference).

        }

        ImGui::EndDragDropTarget();
    }
}
