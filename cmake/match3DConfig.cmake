## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.14)

if (TARGET match3D)
  return()
endif()

include(FetchContent)

function(match3d_fetch_project)
  cmake_parse_arguments(FETCH_SOURCE "" "NAME;URL;DESTINATION" "" ${ARGN})

  FetchContent_Populate(${FETCH_SOURCE_NAME}
    URL ${FETCH_SOURCE_URL}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
  )

  set(
    "${FETCH_SOURCE_NAME}_LOCATION"
    ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
    PARENT_SCOPE
  )
endfunction()

# Use a function to create a localized project() that doesn't impact caller
function(match3D_build_targets)
  project(match3D VERSION 0.5.0 LANGUAGES C CXX)
  subdirs(
    ${CMAKE_CURRENT_LIST_DIR}/../src/glad
    ${CMAKE_CURRENT_LIST_DIR}/../src/imgui
    ${CMAKE_CURRENT_LIST_DIR}/../src/match3D
  )
endfunction()

match3D_build_targets()

set(match3D_FOUND ON)
