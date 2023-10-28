#include "CMesh.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "GameObject.h"

CMesh::CMesh(GameObject* owner) : Component(owner, ComponentType::MESH)
{

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

        //ImGui::Text("Path: %s");
        ImGui::Text("Vertices: %d", nVertices);
        ImGui::Text("Indices: %d", nIndices);
        //ImGui::Text("Normals: %d");
        //ImGui::Text("texture: %d");

        ImGui::Unindent();
    }
}
