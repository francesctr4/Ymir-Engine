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
    /*if (meshShader->path == ShaderEditor::pathToRecompile) {

        meshShader->LoadShader(path);

    }*/

}

void CMaterial::OnInspector()
{
    const char* listShaders[]{ "Loaded", "None", "Chess" };

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    if (ImGui::CollapsingHeader("Material", flags))
    {
        ImGui::Indent();

        ImGui::Spacing();

        //ImGui::Text("Shader Path: %s", meshShader->path.c_str());
        ImGui::Text("Shader: ");
        ImGui::SameLine();
        ImGui::Combo("##ChooseShader", &selectedShader, listShaders, IM_ARRAYSIZE(listShaders));

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
