## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(SimpleApp LANGUAGES CXX)
set(match3D_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(match3D_CACHE_IN_SOURCE_TREE ON)
find_package(match3D REQUIRED COMPONENTS stb_image glm)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE match3D::match3D)
