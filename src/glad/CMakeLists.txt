## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

project(glad VERSION ${PROJECT_VERSION} LANGUAGES C)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME}
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/glad.c>
)
target_link_libraries(${PROJECT_NAME} INTERFACE ${CMAKE_DL_LIBS})

if (MATCH3D_INSTALL_TARGETS)
  install(TARGETS ${PROJECT_NAME}
    EXPORT match3D_glad_Exports
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      NAMELINK_SKIP
    # on Windows put the dlls into bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    # ... and the import lib into the devel package
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

  install(EXPORT match3D_glad_Exports
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/match3D-${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}::
  )
endif()
