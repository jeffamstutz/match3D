// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/detail/Application.h"
// glad
#include "match3D/detail/glad/glad.h"
// glfw
#include <GLFW/glfw3.h>
// imgui
#define IMGUI_DISABLE_INCLUDE_IMCONFIG_H
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
// std
#include <chrono>
#include <cstdio>
#include <stdexcept>

namespace match3D {

static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

struct AppImpl
{
  GLFWwindow *window{nullptr};
  int width{0};
  int height{0};
  bool windowResized{true};
  std::string name;

  std::chrono::time_point<std::chrono::steady_clock> frameEndTime;
  std::chrono::time_point<std::chrono::steady_clock> frameStartTime;

  void init();
  void cleanup();
};

Application::Application()
{
  m_impl = std::make_shared<AppImpl>();
  glfwSetErrorCallback(glfw_error_callback);
}

void Application::run(int width, int height, const char *name)
{
  m_impl->width = width;
  m_impl->height = height;
  m_impl->name = name;

  m_impl->init();
  setup();
  mainLoop();
  teardown();
  m_impl->cleanup();
}

bool Application::getWindowSize(int &width, int &height) const
{
  width = m_impl->width;
  height = m_impl->height;
  return m_impl->windowResized;
}

float Application::getLastFrameLatency() const
{
  auto diff = m_impl->frameEndTime - m_impl->frameStartTime;
  return std::chrono::duration<float>(diff).count();
}

void Application::mainLoop()
{
  auto window = m_impl->window;

  while (!glfwWindowShouldClose(window)) {
    m_impl->frameStartTime = m_impl->frameEndTime;
    m_impl->frameEndTime = std::chrono::steady_clock::now();
    glfwPollEvents();

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    if (io.KeysDown[GLFW_KEY_Q] && io.KeysDown[GLFW_KEY_LEFT_CONTROL])
      glfwSetWindowShouldClose(window, 1);

    buildUI();
    ImGui::Render();

    drawBackground();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    m_impl->windowResized = false;
  }
}

void AppImpl::init()
{
  if (!glfwInit())
    throw std::runtime_error("failed to initialize GLFW");

  glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (window == nullptr)
    throw std::runtime_error("failed to create GLFW window");

  glfwSetWindowUserPointer(window, this);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("Failed to load GL");
  }

  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL2_Init();

  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *w, int newWidth, int newHeight) {
        auto *app = (AppImpl *)glfwGetWindowUserPointer(w);
        app->width = newWidth;
        app->height = newHeight;
        app->windowResized = true;
      });
}

void AppImpl::cleanup()
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  window = nullptr;
}

} // namespace match3D