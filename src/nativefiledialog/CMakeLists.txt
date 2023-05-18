## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

match3D_fetch_project(
  NAME match3D_nativefiledialog
  URL https://github.com/btzy/nativefiledialog-extended/archive/refs/tags/v1.0.3.zip
  MD5 7fd07c47f60a6db4798c705d075e610f
  DESTINATION match3D_nativefiledialog
)

add_subdirectory(
  ${match3D_nativefiledialog_LOCATION}
  ${CMAKE_CURRENT_BINARY_DIR}/nativefiledialog
)
add_library(match3D_nativefiledialog INTERFACE)
target_link_libraries(match3D_nativefiledialog INTERFACE nfd)
