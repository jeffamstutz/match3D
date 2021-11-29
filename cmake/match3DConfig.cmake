## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.14)

if (TARGET match3D OR match3D_FOUND)
  return()
endif()

include(FetchContent)

function(match3D_fetch_project)
  cmake_parse_arguments(FETCH_SOURCE "" "NAME;URL;MD5;DESTINATION" "" ${ARGN})

  if (FETCH_SOURCE_MD5)
    set(FETCH_SOURCE_MD5_COMMAND URL_MD5 ${FETCH_SOURCE_MD5})
  endif()

  FetchContent_Populate(${FETCH_SOURCE_NAME}
    URL ${FETCH_SOURCE_URL}
    ${FETCH_SOURCE_MD5_COMMAND}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
  )

  set(
    "${FETCH_SOURCE_NAME}_LOCATION"
    ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
    PARENT_SCOPE
  )
endfunction()

function(match3D_add_component COMPONENT)
  set(COMP_PATH ${CMAKE_CURRENT_LIST_DIR}/../src/${COMPONENT})
  if (EXISTS ${COMP_PATH})
    add_subdirectory(
      ${COMP_PATH}
      ${CMAKE_CURRENT_BINARY_DIR}/match3D/${COMPONENT}
    )
  else()
    message(FATAL_ERROR "Unknown match3D component given: ${COMP}")
  endif()
endfunction()

# Use a function to create a localized project() that doesn't impact caller
function(match3D_build_targets)
  project(match3D VERSION 0.5.0 LANGUAGES C CXX)

  match3D_add_component(glad)
  match3D_add_component(imgui)
  match3D_add_component(match3D)

  foreach(COMP ${ARGN})
    match3D_add_component(${COMP})
    target_link_libraries(match3D INTERFACE ${COMP})
  endforeach()
endfunction()

match3D_build_targets(${match3D_FIND_COMPONENTS})

set(match3D_FOUND ON)
