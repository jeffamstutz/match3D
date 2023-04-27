// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/match3D.h"
#include "nfd.h"

class NfdApp : public match3D::SimpleApplication
{
 public:
  NfdApp() = default;
  ~NfdApp() override = default;

  void setup() override
  {
    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 1.5f;
    io.IniFilename = nullptr;

    NFD_Init();
  }

  void buildUI() override
  {
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav
        | ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);

    ImGui::Begin("Debug Info", nullptr, windowFlags);

    if (ImGui::Button("Load File")) {
      nfdchar_t *outPath;
      nfdfilteritem_t filterItem[2] = {
          {"Source code", "c,cpp,cc"}, {"Headers", "h,hpp"}};
      nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
      if (result == NFD_OKAY) {
        puts("Success!");
        puts(outPath);
        NFD_FreePath(outPath);
      } else if (result == NFD_CANCEL) {
        puts("User pressed cancel.");
      } else {
        printf("Error: %s\n", NFD_GetError());
      }
    }

    ImGui::End();
  }

  void drawBackground() override
  {
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void teardown() override
  {
    NFD_Quit();
  }
};

int main()
{
  NfdApp app;
  app.run(1280, 800, "NFD application");
}
