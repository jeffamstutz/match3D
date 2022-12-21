// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#include "match3D/detail/SimpleApplication.h"
// glad
#include "match3D/detail/glad/gles2.h"
// glfw
#define GLFW_EXPOSE_NATIVE_EGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
// imgui
#define IMGUI_DISABLE_INCLUDE_IMCONFIG_H
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// std
#include <chrono>
#include <cstdio>
#include <stdexcept>
#include <string>

namespace match3D {

static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

struct SimpleAppImpl
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

SimpleApplication::SimpleApplication()
{
  m_impl = std::make_shared<SimpleAppImpl>();
  glfwSetErrorCallback(glfw_error_callback);
}

void SimpleApplication::run(int width, int height, const char *name)
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

bool SimpleApplication::getWindowSize(int &width, int &height) const
{
  width = m_impl->width;
  height = m_impl->height;
  return m_impl->windowResized;
}

float SimpleApplication::getLastFrameLatency() const
{
  auto diff = m_impl->frameEndTime - m_impl->frameStartTime;
  return std::chrono::duration<float>(diff).count();
}

void SimpleApplication::mainLoop()
{
  auto window = m_impl->window;

  while (!glfwWindowShouldClose(window)) {
    m_impl->frameStartTime = m_impl->frameEndTime;
    m_impl->frameEndTime = std::chrono::steady_clock::now();
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    if (io.KeysDown[GLFW_KEY_Q] && io.KeysDown[GLFW_KEY_LEFT_CONTROL])
      glfwSetWindowShouldClose(window, 1);

    buildUI();
    ImGui::Render();

    drawBackground();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    m_impl->windowResized = false;
  }
}

void SimpleAppImpl::init()
{
  if (!glfwInit())
    throw std::runtime_error("failed to initialize GLFW");

#if 0
  glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
#endif
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

  window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (window == nullptr)
    throw std::runtime_error("failed to create GLFW window");

  glfwSetWindowUserPointer(window, this);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGLES2((GLADloadfunc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("Failed to load GLES");
  }

  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *w, int newWidth, int newHeight) {
        auto *app = (SimpleAppImpl *)glfwGetWindowUserPointer(w);
        app->width = newWidth;
        app->height = newHeight;
        app->windowResized = true;
      });
}

void SimpleAppImpl::cleanup()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  window = nullptr;
}

} // namespace match3D