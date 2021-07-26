## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.14)

if (TARGET match3D)
  return()
endif()

# Use a function to create a localized project() that doesn't impact caller
function(match3D_build_targets)
  project(match3D VERSION 0.5.0 LANGUAGES C CXX)

  set(MATCH3D_LIB_TYPE INTERFACE)
  set(MATCH3D_LINK_MODE INTERFACE)
  set(MATCH3D_SOURCES_MODE INTERFACE)
  set(MATCH3D_INSTALL_TARGETS OFF)

  include(${CMAKE_CURRENT_LIST_DIR}/macros.cmake)

  subdirs(
    ${CMAKE_CURRENT_LIST_DIR}/../src/imgui
    ${CMAKE_CURRENT_LIST_DIR}/../src/match3D
  )
endfunction()

match3D_build_targets()

set(match3D_FOUND ON)
