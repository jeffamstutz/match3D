## Copyright 2020 The Khronos Group
## SPDX-License-Identifier: Apache-2.0

project(stb_image LANGUAGES C)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/stb_image_write.c>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/stb_image.c>
)
target_include_directories(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
