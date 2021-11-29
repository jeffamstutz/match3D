## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

match3D_fetch_project(
  NAME match3D_glm
  URL https://github.com/g-truc/glm/archive/0.9.9.8.zip
  MD5 a421a37d1896ab74765c3f94431ca0f6
  DESTINATION match3D_glm
)

add_library(glm INTERFACE)
target_include_directories(glm
INTERFACE
  $<BUILD_INTERFACE:${match3D_glm_LOCATION}>
)
