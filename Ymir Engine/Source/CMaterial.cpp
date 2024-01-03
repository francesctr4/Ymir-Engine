#include "CMaterial.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleRenderer3D.h"
#include "GameObject.h"

#include "ShaderEditor.h"

CMaterial::CMaterial(GameObject* owner) : Component(owner, ComponentType::MATERIAL)
{
    selectedShader = 0;
}

CMaterial::~CMaterial()
{

}

void CMaterial::Enable()
{

}

void CMaterial::Disable()
{

}

void CMaterial::Update()
{

}

void CMaterial::OnInspector()
{
    std::vector<const char*> listShaderPaths;
    std::vector<const char*> listShaderNames;
    bool shaderDirtyFlag = false; // Introduce a dirty flag

    for (auto& it = Shader::loadedShaders.begin(); it != Shader::loadedShaders.end(); ++it) {
        
        listShaderPaths.push_back(it->first.c_str());

        std::string shaderFileName = std::filesystem::path(it->first).stem().string();
        listShaderNames.push_back(strdup(shaderFileName.c_str())); // strdup to allocate new memory

    }

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::CollapsingHeader("Material", flags))
    {
        ImGui::Indent();

        ImGui::Spacing();

        //ImGui::Text("Shader Path: %s", meshShader->path.c_str());
        ImGui::Text("Shader: ");
        ImGui::SameLine();

        if (ImGui::Combo("##ChooseShader", &selectedShader, listShaderNames.data(), listShaderNames.size())) {
            
            shaderDirtyFlag = true;

        }

        if (shaderDirtyFlag) {

            // Perform actions when selectedShader changes

            for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

                for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

                    if ((*jt).meshGO->selected) {

                        (*jt).shaderPath = listShaderPaths[selectedShader];
                        (*jt).loadedShader = false;

                    }
                }
            }

            // Reset the dirty flag after handling the change
            shaderDirtyFlag = false;

        }

        ImGui::Spacing();

        ImGui::Text("Current .dds UID: %d", 0);

        ImGui::Spacing();

        ImGui::Button("Drop .dds to change texture", ImVec2(200, 50));
        DdsDragDropTarget();

        ImGui::Spacing();

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(ID)), ImVec2(200,200));
        ImGui::Spacing();

        ImGui::Text("Path: %s", path.c_str());
        ImGui::Spacing();

        if (ImGui::Button("Apply Checker Texture")) {

            External->renderer3D->ApplyCheckerTexture();

        }

        ImGui::Spacing();

        if (ImGui::Button("Clear Actual Texture")) {

            External->renderer3D->ClearActualTexture();

        }

        ImGui::Spacing();

        ImGui::Unindent();
    }

}

void CMaterial::DdsDragDropTarget()
{
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("dds"))
        {
            std::string* libraryFilePathDrop = (std::string*)payload->Data;

            // Unload Resource of the previous texture loaded if it had any

            // Retrieve name of the file dropped, and then get the UID.

            // Lastly, Request Resource of the Texture with given UID, Path and Type and render it (add a reference).

        }

        ImGui::EndDragDropTarget();
    }
}
