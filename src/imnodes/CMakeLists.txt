## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(match3D_imnodes VERSION ${PROJECT_VERSION} LANGUAGES CXX)

match3D_fetch_project(
  NAME match3D_imnodes_src
  URL https://github.com/Nelarius/imnodes/archive/e563371cee49eb42da08cca1e0209d30d452c665.zip
  MD5 b4e87cdd549a759907bbb7cf5176ace8
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
