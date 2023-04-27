## Copyright 2021 Jefferson Amstutz
## SPDX-License-Identifier: Apache-2.0

set(match3D_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(match3D_CACHE_IN_SOURCE_TREE ON)
find_package(match3D REQUIRED COMPONENTS stb_image glm imnodes nativefiledialog)

add_subdirectory(docking)
add_subdirectory(nfd)
add_subdirectory(nodes)
add_subdirectory(simple)
