## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(imgui_glfw VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3d_fetch_project(
  NAME match3D_imgui_src
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.82.zip
  DESTINATION match3D_imgui
)

set(OpenGL_GL_PREFERENCE "LEGACY")
if (MATCH3D_SRC_CONFIG_MODE)
  find_dependency(OpenGL 4)
  find_dependency(glfw3)
else()
  find_package(OpenGL 4 REQUIRED)
  find_package(glfw3 REQUIRED)
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE
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
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/match3D/detail>
)

if (MATCH3D_INSTALL_TARGETS)
  install(TARGETS ${PROJECT_NAME}
    EXPORT match3D_imgui_Exports
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      NAMELINK_SKIP
    # on Windows put the dlls into bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    # ... and the import lib into the devel package
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

  install(EXPORT match3D_imgui_Exports
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/match3D-${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}::
  )

  install(FILES ${match3D_imgui_src_LOCATION}/imgui.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/match3D/detail
  )
endif()
