#include "CTransform.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

CTransform::CTransform(GameObject* owner) : Component(owner, ComponentType::TRANSFORM)
{
    translation = float3::zero;
    rotation = float3::zero;
    scale = float3::zero;

    translationPtr = nullptr;
    rotationPtr = nullptr;
    scalePtr = nullptr;

    resetPressed = false;

    mGlobalMatrix = float4x4::identity;

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

                    translation = (*jt).meshShader.translation;
                    rotation = (*jt).meshShader.rotation;
                    scale = (*jt).meshShader.scale;

                    translationPtr = &(*jt).meshShader.translation;
                    rotationPtr = &(*jt).meshShader.rotation;
                    scalePtr = &(*jt).meshShader.scale;

                    ImGui::DragFloat3("Transform", (*translationPtr).ptr(), 0.1f);
                    ImGui::DragFloat3("Rotation", (*rotationPtr).ptr(), 0.1f);
                    ImGui::DragFloat3("Scale", (*scalePtr).ptr(), 0.1f);

                    if (ImGui::Button("Reset Transformations")) {

                        (*jt).meshShader.Translate({ 0,0,0 });
                        (*jt).meshShader.Rotate({ 0,0,0 });
                        (*jt).meshShader.Scale({ 1,1,1 });

                        resetPressed = true;

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
