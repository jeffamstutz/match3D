## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(match3D_imgui_glfw VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3D_fetch_project(
  NAME match3D_imgui_src
  # v1.87 docking branch
  URL https://github.com/ocornut/imgui/archive/505f19e3b00d54623566dda354980c7f3410f2b5.zip
  MD5 b21e2a4a910c3b0320a6758535e3082b
  DESTINATION match3D_imgui
)

include(CMakeFindDependencyMacro)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_dependency(OpenGL 4)
find_dependency(glfw3)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/imgui.cpp>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/imgui_draw.cpp>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/imgui_demo.cpp>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/imgui_tables.cpp>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/imgui_widgets.cpp>

  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/backends/imgui_impl_glfw.cpp>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/backends/imgui_impl_opengl2.cpp>

  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/misc/cpp/imgui_stdlib.cpp>
)

target_link_libraries(${PROJECT_NAME} INTERFACE glfw OpenGL::GL)

target_include_directories(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/backends>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/misc/cpp>
)
