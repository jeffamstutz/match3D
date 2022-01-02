// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/match3D.h"

class DemoWindow : public match3D::Window
{
 public:
  DemoWindow() : match3D::Window("Demo Window", true, false) {}

  void buildUI() override
  {
    ImGui::ShowDemoWindow();
  }
};

class DockingApp : public match3D::DockingApplication
{
 public:
  DockingApp() = default;
  ~DockingApp() override = default;

  match3D::WindowArray setup() override
  {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    io.IniFilename = nullptr;

    match3D::WindowArray windows;
    windows.emplace_back(new DemoWindow());
    return windows;
  }

  void buildMainMenuUI() override
  {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("example item 1"))
          printf("example item 1 pressed\n");

        if (ImGui::MenuItem("example item 2"))
          printf("example item 2 pressed\n");

        ImGui::Separator();

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
    // nothing to tear down
  }
};

int main()
{
  DockingApp app;
  app.run(1280, 800, "Example docking match3D application");
}
