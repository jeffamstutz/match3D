## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(NodesApp LANGUAGES CXX)
add_executable(${PROJECT_NAME} ui_layout.cpp main.cpp NodeGraph.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE match3D::match3D)
