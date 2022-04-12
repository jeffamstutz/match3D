## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(match3D_imnodes VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3D_fetch_project(
  NAME match3D_imnodes_src
  URL https://github.com/Nelarius/imnodes/archive/refs/tags/v0.5.zip
  MD5 bebc93614fb55fc5924191b3c5320026
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

target_compile_definitions(${PROJECT_NAME} INTERFACE MATCH3D_WITH_IMNODES)
