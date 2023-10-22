#include "CTransform.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

CTransform::CTransform(GameObject* owner) : Component(owner, ComponentType::TRANSFORM)
{

}

CTransform::~CTransform()
{

}

void CTransform::Enable()
{

}

void CTransform::Disable()
{

}

void CTransform::Update()
{

}

void CTransform::OnInspector()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::CollapsingHeader("Transform", flags))
    {
        ImGui::Indent();

        float position[] = { 0,0,0 };
        ImGui::InputFloat3("Transform", position);
        float rotation[] = { 1,0,0,0 };
        ImGui::InputFloat4("Rotation", rotation);
        float scale[] = { 1,1,1 };
        ImGui::InputFloat3("Scale", scale);

        ImGui::Unindent();
    }
}

void CTransform::SetPosition()
{

}

void CTransform::SetRotation()
{

}

void CTransform::SetScale()
{

}
