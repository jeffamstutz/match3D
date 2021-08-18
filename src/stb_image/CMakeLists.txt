## Copyright 2020 The Khronos Group
## SPDX-License-Identifier: Apache-2.0

project(stb_image LANGUAGES C)
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:stb_image_write.c>
  $<BUILD_INTERFACE:stb_image.c>
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})
