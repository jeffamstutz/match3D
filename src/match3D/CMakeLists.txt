## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

add_library(${PROJECT_NAME} ${MATCH3D_LIB_TYPE} Application.cpp)
target_sources(${PROJECT_NAME} ${MATCH3D_SOURCES_MODE} Application.cpp)
target_link_libraries(${PROJECT_NAME} ${MATCH3D_LINK_MODE} imgui_glfw)
target_include_directories(${PROJECT_NAME}
${MATCH3D_LINK_MODE}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

if (MATCH3D_INSTALL_TARGETS)
  install(TARGETS ${PROJECT_NAME}
    EXPORT match3D_Exports
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      NAMELINK_SKIP
    # on Windows put the dlls into bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    # ... and the import lib into the devel package
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

  install(EXPORT match3D_Exports
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/match3D-${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}::
  )

  install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      NAMELINK_ONLY
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/match3D
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
else()
  add_library(match3D::match3D ALIAS match3D)
endif()
