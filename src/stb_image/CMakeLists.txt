## Copyright 2020 The Khronos Group
## SPDX-License-Identifier: Apache-2.0

project(stb_image LANGUAGES C)
add_library(${PROJECT_NAME} STATIC stb_image_write.c stb_image.c)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})