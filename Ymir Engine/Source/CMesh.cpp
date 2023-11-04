#include "CMesh.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"


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

                    ImGui::Checkbox("Show Normal Map", &(*jt).showNormalMap);
                    ImGui::Spacing();

                }

            }

        }

        ImGui::Unindent();
    }
}
