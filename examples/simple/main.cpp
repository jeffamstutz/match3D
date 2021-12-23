// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/match3D.h"
// NOTE: Also can include glm and stb_image because they were passed as CMake
//       components. If those were omitted in CMake, then only match3D/match3D.h
//       can be included.
#include "glm/glm.hpp"
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

class ExampleApp : public match3D::Application
{
 public:
  ExampleApp() = default;
  ~ExampleApp() override = default;

  void setup() override
  {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
  }

  void buildUI() override
  {
    ImGui::ShowDemoWindow();

    {
      ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration
          | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings
          | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav
          | ImGuiWindowFlags_NoMove;

      ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

      ImGui::Begin("Debug Info", nullptr, windowFlags);

      ImGuiIO &io = ImGui::GetIO();
      ImGui::Text("display rate: %.1f FPS", 1.f / getLastFrameLatency());
      ImGui::Text("mouse pos: %f, %f", io.MousePos.x, io.MousePos.y);
      ImGui::NewLine();

      const bool leftMouseClick = ImGui::IsMouseDown(ImGuiMouseButton_Left);
      ImGui::Text("%s", leftMouseClick ? "*click*" : "");
      ImGui::End();
    }
  }

  void drawBackground() override
  {
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void teardown() override
  {
    // nothing to tear down
  }
};

int main()
{
  ExampleApp app;
  app.run(1280, 800, "Example match3D application");
}
