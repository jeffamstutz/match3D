// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/detail/Application.h"
// glfw
#include <GLFW/glfw3.h>
// imgui
#define IMGUI_DISABLE_INCLUDE_IMCONFIG_H
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
// std
#include <cstdio>
#include <stdexcept>

namespace match {

static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

struct AppImpl
{
  GLFWwindow *window{nullptr};
  size_t width;
  size_t height;
  std::string name;

  void init();
  void cleanup();
};

Application::Application()
{
  m_impl = std::make_shared<AppImpl>();
  glfwSetErrorCallback(glfw_error_callback);
}

void Application::run(size_t width, size_t height, const char *name)
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

void Application::mainLoop()
{
  auto window = m_impl->window;

  while (!glfwWindowShouldClose(window)) {
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
  }
}

void AppImpl::init()
{
  if (!glfwInit())
    throw std::runtime_error("failed to initialize GLFW");

  window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

  if (window == nullptr)
    throw std::runtime_error("failed to create GLFW window");

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL2_Init();
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

} // namespace match