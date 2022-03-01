## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(match3D_glad VERSION ${PROJECT_VERSION} LANGUAGES C)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/glad.c>
)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_DL_LIBS})
