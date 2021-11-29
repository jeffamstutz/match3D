## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(imnodes VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3D_fetch_project(
  NAME match3D_imnodes_src
  URL https://github.com/Nelarius/imnodes/archive/refs/tags/v0.4.zip
  MD5 0681a747526030b0c4f3c4f68f3133b9
  DESTINATION match3D_imnodes
)

include(CMakeFindDependencyMacro)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${match3D_imnodes_src_LOCATION}/imnodes.cpp>
)

target_link_libraries(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${match3D_imnodes_src_LOCATION}>
)
