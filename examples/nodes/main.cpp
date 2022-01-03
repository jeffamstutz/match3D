// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "NodeGraph.h"
// match3D
#include "match3D/match3D.h"

extern const char *getDefaultUILayout();

// Node types /////////////////////////////////////////////////////////////////

class SourceNode : public Node
{
 public:
  SourceNode() : Node("Source")
  {
    m_outgoing.emplace_back("source", this);
  }
};

class ComputeNode : public Node
{
 public:
  ComputeNode() : Node("Compute")
  {
    m_incoming.emplace_back("input", this);
    m_outgoing.emplace_back("output", this);
  }
};

class SinkNode : public Node
{
 public:
  SinkNode() : Node("Sink")
  {
    m_incoming.emplace_back("sink", this);
  }
};

// Window types ///////////////////////////////////////////////////////////////

class DemoWindow : public match3D::Window
{
 public:
  DemoWindow() : match3D::Window("Demo Window", true, false) {}

  void buildUI() override
  {
    ImGui::ShowDemoWindow();
  }
};

class NodeEditor : public match3D::Window
{
 public:
  NodeEditor(NodeGraph *graph)
      : match3D::Window("NodeEditor", true), m_graph(graph)
  {}

  void buildUI() override
  {
    ImNodes::BeginNodeEditor();

    contextMenu();

    for (auto &n : m_graph->nodes()) {
      ImNodes::BeginNode(n->id());
      ImNodes::BeginNodeTitleBar();
      ImGui::Text("%s", n->name());
      ImNodes::EndNodeTitleBar();
      ImGui::Dummy(ImVec2(80.0f, 10.0f));

      bool bothInAndOut = !n->incoming().empty() && !n->outgoing().empty();

      for (auto &ip : n->incoming()) {
        ImNodes::BeginInputAttribute(ip.id());
        ImGui::Text("%s", ip.name());
        ImNodes::EndInputAttribute();
      }

      if (bothInAndOut)
        ImGui::Dummy(ImVec2(80.0f, 10.0f));

      for (auto &op : n->outgoing()) {
        ImNodes::BeginOutputAttribute(op.id());
        ImGui::Text("%s", op.name());
        ImNodes::EndOutputAttribute();
      }

      ImNodes::EndNode();
    }

    for (auto &l : m_graph->links())
      ImNodes::Link(l.id(), l.from->id(), l.to->id());

    ImNodes::MiniMap();
    ImNodes::EndNodeEditor();

    int startID, endID;
    if (ImNodes::IsLinkCreated(&startID, &endID))
      m_graph->addLink(startID, endID);

    const bool doDelete = ImGui::IsKeyReleased(GLFW_KEY_DELETE)
        || ImGui::IsKeyReleased(GLFW_KEY_X);

    int numSelected = ImNodes::NumSelectedLinks();
    if (numSelected > 0 && doDelete) {
      static std::vector<int> selectedLinks;
      selectedLinks.resize(numSelected);
      ImNodes::GetSelectedLinks(selectedLinks.data());
      for (const int linkID : selectedLinks)
        m_graph->removeLink(linkID);
    }

    numSelected = ImNodes::NumSelectedNodes();
    if (numSelected > 0 && doDelete) {
      static std::vector<int> selectedNodes;
      selectedNodes.resize(numSelected);
      ImNodes::GetSelectedNodes(selectedNodes.data());
      for (const int linkID : selectedNodes)
        m_graph->removeNode(linkID);
    }
  }

  void contextMenu()
  {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));

    ImGuiIO &io = ImGui::GetIO();
    const bool openMenu =
        io.KeysDown[GLFW_KEY_A] && io.KeysDown[GLFW_KEY_LEFT_SHIFT];

    static auto mousePos = ImGui::GetMousePos();

    if (openMenu && ImNodes::IsEditorHovered()) {
      m_contextMenuVisible = true;
      mousePos = ImGui::GetMousePos();
      ImGui::OpenPopup("vpContextMenu");
    }

    if (ImGui::BeginPopup("vpContextMenu")) {
      if (ImGui::BeginMenu("add node")) {
        const auto &nodes = m_graph->nodes();
        const auto numNodes = nodes.size();

        if (ImGui::MenuItem("source"))
          m_graph->addNode(make_Node<SourceNode>());
        if (ImGui::MenuItem("compute"))
          m_graph->addNode(make_Node<ComputeNode>());
        if (ImGui::MenuItem("sink"))
          m_graph->addNode(make_Node<SinkNode>());

        if (numNodes != nodes.size())
          ImNodes::SetNodeScreenSpacePos(nodes.back()->id(), mousePos);

        ImGui::EndMenu();
      }

      if (!ImGui::IsPopupOpen("vpContextMenu"))
        m_contextMenuVisible = false;

      ImGui::EndPopup();
    }

    ImGui::PopStyleVar(1);
  }

 private:
  bool m_contextMenuVisible{false};
  NodeGraph *m_graph{nullptr};
};

// Main application ///////////////////////////////////////////////////////////

class NodesApp : public match3D::DockingApplication
{
 public:
  NodesApp() = default;
  ~NodesApp() override = default;

  match3D::WindowArray setup() override
  {
    ImNodes::CreateContext();

    ImNodesStyle &style = ImNodes::GetStyle();
    style.Colors[ImNodesCol_TitleBar] = IM_COL32(200, 9, 25, 255);
    style.Colors[ImNodesCol_TitleBarHovered] = IM_COL32(232, 27, 86, 255);
    style.Colors[ImNodesCol_TitleBarSelected] = IM_COL32(255, 80, 80, 255);

    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    io.IniFilename = nullptr;

    ImGui::LoadIniSettingsFromMemory(getDefaultUILayout());

    m_graph.addNode(make_Node<SourceNode>());

    match3D::WindowArray windows;
    windows.emplace_back(new DemoWindow());
    windows.emplace_back(new NodeEditor(&m_graph));
    return windows;
  }

  void buildMainMenuUI() override
  {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("print ImGui ini")) {
          const char *info = ImGui::SaveIniSettingsToMemory();
          printf("%s\n", info);
        }

        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
  }

  void teardown() override
  {
    ImNodes::DestroyContext();
  }

 private:
  NodeGraph m_graph;
};

int main()
{
  NodesApp app;
  app.run(1280, 800, "Example nodes match3D application");
}
