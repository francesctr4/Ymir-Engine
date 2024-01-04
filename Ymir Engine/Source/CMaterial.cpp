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
    bool shaderDirtyFlag = false; 

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

        ImGui::SeparatorText("SHADER");

        ImGui::Spacing();

        //ImGui::Text("Shader Path: %s", meshShader->path.c_str());
        ImGui::Text("Shader: ");
        ImGui::SameLine();

        // Find the index of the current shader path in listShaderPaths
        for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

            for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

                if ((*jt).meshGO->selected) {

                    // Find the index of the current shader path in listShaderPaths
                    auto it = std::find(listShaderPaths.begin(), listShaderPaths.end(), (*jt).shaderPath);

                    if (it != listShaderPaths.end()) {

                        selectedShader = static_cast<int>(std::distance(listShaderPaths.begin(), it));

                    }

                }

            }

        }

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

        // Shader Uniforms Management

        for (auto it = External->renderer3D->models.begin(); it != External->renderer3D->models.end(); ++it) {

            for (auto jt = (*it).meshes.begin(); jt != (*it).meshes.end(); ++jt) {

                if ((*jt).meshGO->selected) {

                    if ((*jt).meshShader.uniforms.size() == 0) {

                        ImGui::Text("No editable uniforms.");

                    }
                    else {

                        ImGui::Text("Uniforms:");

                    }

                    ImGui::Spacing();

                    ImGui::Indent();

                    for (auto kt = jt->meshShader.uniforms.begin(); kt != jt->meshShader.uniforms.end(); ++kt) {

                        ImGui::Text("%s", kt->name.c_str());

                        ImGui::SameLine();

                        std::string label = "##" + kt->name;

                        switch (kt->type) {

                            case UniformType::i1:
                            case UniformType::f1: {
                            
                                ImGui::DragFloat(label.c_str(), (float*)kt->value, 0.1f);

                                // Set the new value for the uniform
                                jt->meshShader.SetUniformValue(kt->name, (float*)kt->value);
                                break;
                            }
                        // Add cases for other uniform types as needed
                        }

                    }

                    ImGui::Unindent();

                    //ImGui::Text("Water Speed: ");

                    //ImGui::SameLine();

                    //ImGui::PushItemWidth(100);
                    //ImGui::DragFloat("##WaterSpeed", &(*jt).meshShader.waterShaderSpeed, 0.1f);
                    //ImGui::PopItemWidth();

                }

            }

        }

        /*for (size_t i = 0; i < shader->uniforms.size(); i++) {

            switch (shader->uniforms[i].valueType) {
            case UniformType::f1:
            {
                ImGui::InputFloat(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
            }
            break;
            case UniformType::f2:
            {
                ImGui::InputFloat2(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
            }
            break;
            case UniformType::f3:
            {
                ImGui::InputFloat3(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
            }
            break;
            case UniformType::f4:
            {
                ImGui::InputFloat4(shader->uniforms[i].name.c_str(), (float*)shader->uniforms[i].value);
            }
            break;
            case UniformType::i1:
            {
                ImGui::InputInt(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
            }
            break;
            case UniformType::i2:
            {
                ImGui::InputInt2(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
            }
            break;
            case UniformType::i3:
            {
                ImGui::InputInt3(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
            }
            break;
            case UniformType::i4:
            {
                ImGui::InputInt4(shader->uniforms[i].name.c_str(), (int*)shader->uniforms[i].value);
            }
            break;
            }
        }*/

        ImGui::Spacing();

        ImGui::SeparatorText("TEXTURES");

        ImGui::Spacing();

        ImVec2 textureMapSize(20, 20);

        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(ID)), textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Diffuse");
        ImGui::SameLine();
        ImGui::Text("(%s)", path.c_str());

        ImGui::Spacing();

        ImGui::ColorButton("Specular", ImVec4(0, 0, 0, 0), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder, textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Specular");

        ImGui::Spacing();

        ImGui::ColorButton("Normal", ImVec4(0, 0, 0, 0), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder, textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Normal");

        ImGui::Spacing();

        ImGui::ColorButton("Height", ImVec4(0, 0, 0, 0), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder, textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Height");

        ImGui::Spacing();

        ImGui::ColorButton("Ambient", ImVec4(0, 0, 0, 0), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder, textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Ambient");

        ImGui::Spacing();

        ImGui::ColorButton("Emissive", ImVec4(0, 0, 0, 0), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoBorder, textureMapSize);
        DdsDragDropTarget();
        ImGui::SameLine();
        ImGui::Text("Emissive");

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
