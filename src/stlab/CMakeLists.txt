## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

match3D_fetch_project(
  NAME match3D_stlab
  URL https://github.com/jeffamstutz/stlab_libraries/archive/refs/heads/main.zip
  DESTINATION match3D_stlab
)

add_library(stlab INTERFACE)
target_include_directories(stlab
INTERFACE
  $<BUILD_INTERFACE:${match3D_stlab_LOCATION}>
)
