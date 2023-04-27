## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

match3D_fetch_project(
  NAME match3D_nativefiledialog
  URL https://github.com/btzy/nativefiledialog-extended/archive/refs/heads/master.zip
  MD5 53a229ad013bba73b2edf22418dc46cd
  DESTINATION match3D_nativefiledialog
)

add_subdirectory(
  ${match3D_nativefiledialog_LOCATION}
  ${CMAKE_BINARY_DIR}/match3D/nativefiledialog
)
add_library(match3D_nativefiledialog INTERFACE)
target_link_libraries(match3D_nativefiledialog INTERFACE nfd)
