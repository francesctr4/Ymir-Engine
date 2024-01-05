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
    ID = 0;
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
    // Vectors of shader paths and names
    std::vector<const char*> listShaderPaths;
    std::vector<const char*> listShaderNames;
    bool shaderDirtyFlag = false; 

    // Manage loaded shaders
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

        // ------------------------------------ SHADER ------------------------------------

        ImGui::SeparatorText("SHADER");

        ImGui::Spacing();

        ImGui::Text("Shader: ");
        ImGui::SameLine();

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

        // Choose between the list of shaders
        if (ImGui::Combo("##ChooseShader", &selectedShader, listShaderNames.data(), listShaderNames.size())) {
            
            shaderDirtyFlag = true;

        }

        if (shaderDirtyFlag) {

            // When selected shader changes, update the shader path and recompile
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
                    
                    // In case the shader has editable uniforms:
                    for (auto kt = jt->meshShader.uniforms.begin(); kt != jt->meshShader.uniforms.end(); ++kt) {

                        std::string label = "##" + kt->name;

                        ImGui::Text("%s", kt->name.c_str());
                        ImGui::SameLine();

                        // Change display according to uniform type
                        switch (kt->type)
                        {
                        case UniformType::boolean:

                            ImGui::Checkbox(label.c_str(), (bool*)kt->value);

                            jt->meshShader.SetUniformValue(kt->name, (bool*)kt->value);

                            break;

                        case UniformType::i1:

                            ImGui::DragInt(label.c_str(), (int*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (int*)kt->value);

                            break;

                        case UniformType::i2:

                            ImGui::DragInt2(label.c_str(), (int*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (int*)kt->value);

                            break;

                        case UniformType::i3:

                            ImGui::DragInt3(label.c_str(), (int*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (int*)kt->value);

                            break;

                        case UniformType::i4:

                            ImGui::DragInt4(label.c_str(), (int*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (int*)kt->value);

                            break;

                        case UniformType::f1:

                            ImGui::DragFloat(label.c_str(), (float*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (float*)kt->value);

                            break;

                        case UniformType::f2:

                            ImGui::DragFloat2(label.c_str(), (float*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (float*)kt->value);

                            break;

                        case UniformType::f3:

                            ImGui::DragFloat3(label.c_str(), (float*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (float*)kt->value);

                            break;

                        case UniformType::f4:

                            ImGui::DragFloat4(label.c_str(), (float*)kt->value, 0.1f);

                            jt->meshShader.SetUniformValue(kt->name, (float*)kt->value);

                            break;

                        }

                    }

                    ImGui::Unindent();

                }

            }

        }

        ImGui::Spacing();

        // ------------------------------------ TEXTURES ------------------------------------

        ImGui::SeparatorText("TEXTURES");

        ImGui::Spacing();

        // Display texture maps of the gameobject material

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

        // Utility buttons

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

            // Unload Resource of the previous texture loaded if it had any.

            // Retrieve name of the file dropped, and then get the UID.

            // Lastly, Request Resource of the Texture with given UID, Path and Type and render it (add a reference).

        }

        ImGui::EndDragDropTarget();
    }
}
