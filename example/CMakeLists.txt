## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(ExampleApp LANGUAGES CXX)
set(match3D_DIR ${CMAKE_CURRENT_LIST_DIR}../cmake)
find_package(match3D REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE match3D::match3D)
