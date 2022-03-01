## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
  SimpleApplication.cpp
  DockingApplication.cpp
  Window.cpp
)
target_link_libraries(${PROJECT_NAME} INTERFACE match3D_imgui_glfw match3D_glad)
target_include_directories(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

add_library(match3D::match3D ALIAS match3D)
