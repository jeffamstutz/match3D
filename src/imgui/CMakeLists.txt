## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(match3D_imgui_glfw VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3D_fetch_project(
  NAME match3D_imgui_src
  # v1.89 docking branch
  URL https://github.com/ocornut/imgui/archive/9964740a47fda96ee937cfea272ccac85dc6a500.zip
  MD5 8294d2fbceafcda4ebddf38f4ea2d4e8
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
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/backends/imgui_impl_opengl3.cpp>

  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/misc/cpp/imgui_stdlib.cpp>
)

target_link_libraries(${PROJECT_NAME} INTERFACE glfw OpenGL::GL)

target_compile_definitions(${PROJECT_NAME}
INTERFACE
  IMGUI_IMPL_OPENGL_LOADER_GLAD2
  IMGUI_IMPL_OPENGL_ES3
)

target_include_directories(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/backends>
  $<BUILD_INTERFACE:${match3D_imgui_src_LOCATION}/misc/cpp>
)
