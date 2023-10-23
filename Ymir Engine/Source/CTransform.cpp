#include "CTransform.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

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

        for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

            for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

                if ((*jt).meshGO->selected || (*it).modelGO->selected) {

                    ImGui::DragFloat3("Transform", (*jt).meshShader.translation.ptr(), 0.1f);
                    ImGui::DragFloat3("Rotation", (*jt).meshShader.rotation.ptr(), 0.1f);
                    ImGui::DragFloat3("Scale", (*jt).meshShader.scale.ptr(), 0.1f);

                    translation = (*jt).meshShader.translation;
                    rotation = (*jt).meshShader.rotation;
                    scale = (*jt).meshShader.scale;

                    ImGui::Spacing();

                    if (ImGui::Button("Reset Transformations")) {

                        (*jt).meshShader.Translate({ 0,0,0 });
                        (*jt).meshShader.Rotate({ 0,0,0 });
                        (*jt).meshShader.Scale({ 1,1,1 });

                    }

                }
                
            }

        }

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
