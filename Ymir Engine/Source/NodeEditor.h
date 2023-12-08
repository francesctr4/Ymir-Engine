#pragma once

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "External/ImGuiNodeEditor/include/imgui_node_editor.h"

namespace NodeEditor = ax::NodeEditor;

/* Struct to hold basic information about connection between pins.Note that connection(aka.link) has its own ID.
This is useful later with dealing with selections, deletion or other operations. */

struct LinkInfo
{
    NodeEditor::LinkId linkID;
    NodeEditor::PinId inputID;
    NodeEditor::PinId outputID;
};

class NodeEditorWindow {
public:

    NodeEditorWindow();
    virtual ~NodeEditorWindow();

    void Create();
    void Destroy();
    void Update();

private:

    void NodePinBeginColumn();
    void NodePinNextColumn();
    void NodePinEndColumn();

private:

    // Editor context, required to trace a editor state.
    NodeEditor::EditorContext* mContext; 

    // Flag set for first frame only, some action need to be executed once.
    bool mFirstFrame; 

    // List of live links. It is dynamic unless you want to create read-only view over nodes.
    ImVector<LinkInfo> mLinks; 

    // Counter to help generate link ids. In real application this will probably based on pointer to user data structure.
    int mNextLinkID; 

};