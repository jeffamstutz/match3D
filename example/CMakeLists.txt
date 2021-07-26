## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(ExampleApp LANGUAGES CXX)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE match3D)
