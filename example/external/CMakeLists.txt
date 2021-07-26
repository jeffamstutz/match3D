## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.14)
project(ExampleAppExternal LANGUAGES CXX)
find_package(match3D REQUIRED)
add_executable(${PROJECT_NAME} ../main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE match3D::match3D)
