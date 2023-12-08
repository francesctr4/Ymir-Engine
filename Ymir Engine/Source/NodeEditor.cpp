#include "NodeEditor.h"

NodeEditorWindow::NodeEditorWindow()
{
    mContext = nullptr;
    mFirstFrame = true;
    mNextLinkID = 100;
}

NodeEditorWindow::~NodeEditorWindow()
{

}

void NodeEditorWindow::Create() {

    NodeEditor::Config config;
    config.SettingsFile = "NodeEditor.json";

    mContext = NodeEditor::CreateEditor(&config);

}

void NodeEditorWindow::Destroy() {

    NodeEditor::DestroyEditor(mContext);

}

void NodeEditorWindow::Update() {

    NodeEditor::SetCurrentEditor(mContext);

    // Start interaction with editor.
    if (NodeEditor::Begin("Node Editor", ImVec2(0.0, 0.0f)), true) {

        int UID = 1;

        // ------------------------- NODES ----------------------------

        // 1) Commit known data to editor

        // Node A

        NodeEditor::NodeId nodeA_ID = UID++;
        NodeEditor::PinId nodeA_InputPinID = UID++;
        NodeEditor::PinId nodeA_OutputPinID = UID++;

        if (mFirstFrame) {

            NodeEditor::SetNodePosition(nodeA_ID, ImVec2(10, 10));

        }
            
        if (NodeEditor::BeginNode(nodeA_ID), true) {

            ImGui::Text("Node A");

            if (NodeEditor::BeginPin(nodeA_InputPinID, NodeEditor::PinKind::Input), true) {

                ImGui::Text("-> In");

                NodeEditor::EndPin();
            }
            
            ImGui::SameLine();

            if (NodeEditor::BeginPin(nodeA_OutputPinID, NodeEditor::PinKind::Output), true) {

                ImGui::Text("Out ->");

                NodeEditor::EndPin();
            }
            
            NodeEditor::EndNode();
        }
        
        // Node B

        NodeEditor::NodeId nodeB_ID = UID++;
        NodeEditor::PinId nodeB_InputPinID1 = UID++;
        NodeEditor::PinId nodeB_InputPinID2 = UID++;
        NodeEditor::PinId nodeB_OutputPinID = UID++;

        if (mFirstFrame) {

            NodeEditor::SetNodePosition(nodeB_ID, ImVec2(210, 60));

        }

        if (NodeEditor::BeginNode(nodeB_ID), true) {

            ImGui::Text("Node B");

            NodePinBeginColumn();

            if (NodeEditor::BeginPin(nodeB_InputPinID1, NodeEditor::PinKind::Input), true) {

                ImGui::Text("-> In 1");

                NodeEditor::EndPin();
            }

            if (NodeEditor::BeginPin(nodeB_InputPinID2, NodeEditor::PinKind::Input), true) {

                ImGui::Text("-> In 2");

                NodeEditor::EndPin();
            }

            NodePinNextColumn();

            if (NodeEditor::BeginPin(nodeB_OutputPinID, NodeEditor::PinKind::Output), true) {

                ImGui::Text("Out ->");

                NodeEditor::EndPin();
            }

            NodePinEndColumn();

            NodeEditor::EndNode();
        }

        // Submit Links
        for (auto& linkInfo : mLinks) {

            NodeEditor::Link(linkInfo.linkID, linkInfo.inputID, linkInfo.outputID);

        }

        // 2) Handle interactions.

        // Handle creation action, returns true if editor want to create new object (node or link).
        if (NodeEditor::BeginCreate())
        {
            NodeEditor::PinId inputPinID, outputPinID;

            if (NodeEditor::QueryNewLink(&inputPinID, &outputPinID))
            {
                // QueryNewLink returns true if editor want to create new link between pins.
                
                // Link can be created only for two valid pins, it is up to you to
                // validate if connection make sense. Editor is happy to make any.
                
                // Link always goes from input to output. User may choose to drag
                // link from output pin or input pin. This determine which pin ids
                // are valid and which are not:
                //   * input valid, output invalid - user started to drag new ling from input pin
                //   * input invalid, output valid - user started to drag new ling from output pin
                //   * input valid, output valid   - user dragged link over other pin, can be validated

                if (inputPinID && outputPinID) // both are valid, let's accept link
                {
                    // ed::AcceptNewItem() return true when user release mouse button.
                    if (NodeEditor::AcceptNewItem())
                    {
                        // Since we accepted new link, lets add one to our list of links.
                        mLinks.push_back({ NodeEditor::LinkId(mNextLinkID++), inputPinID, outputPinID });

                        // Draw new link.
                        NodeEditor::Link(mLinks.back().linkID, mLinks.back().inputID, mLinks.back().outputID);
                    }

                    // You may choose to reject connection between these nodes
                    // by calling ed::RejectNewItem(). This will allow editor to give
                    // visual feedback by changing link thickness and color.
                }
            }
        }

        NodeEditor::EndCreate(); // Wraps up object creation action handling.

        // Handle deletion action
        if (NodeEditor::BeginDelete())
        {
            // There may be many links marked for deletion, let's loop over them.
            NodeEditor::LinkId deletedLinkID;

            while (NodeEditor::QueryDeletedLink(&deletedLinkID))
            {
                // If you agree that link can be deleted, accept deletion.
                if (NodeEditor::AcceptDeletedItem())
                {
                    // Then remove link from your data.
                    for (auto& link : mLinks)
                    {
                        if (link.linkID == deletedLinkID)
                        {
                            mLinks.erase(&link);
                            break; 
                        }
                    }
                }

                // You may reject link deletion by calling:
                // ed::RejectDeletedItem();
            }
        }
        NodeEditor::EndDelete(); // Wrap up deletion action
           
        // End of interaction with editor.
        NodeEditor::End();
    }

    if (mFirstFrame) {

        NodeEditor::NavigateToContent(0.0f);

    }
        
    NodeEditor::SetCurrentEditor(nullptr);

    mFirstFrame = false;
}

void NodeEditorWindow::NodePinBeginColumn()
{
    ImGui::BeginGroup();
}

void NodeEditorWindow::NodePinNextColumn()
{
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
}

void NodeEditorWindow::NodePinEndColumn()
{
    ImGui::EndGroup();
}