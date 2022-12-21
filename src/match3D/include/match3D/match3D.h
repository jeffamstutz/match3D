// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#pragma once

// glad
#include "detail/glad/gles2.h"
// glfw
#include <GLFW/glfw3.h>
// imgui
#define IMGUI_DISABLE_INCLUDE_IMCONFIG_H
#include <imgui.h>
// match3D
#include "detail/DockingApplication.h"
#include "detail/SimpleApplication.h"

#ifdef MATCH3D_WITH_IMNODES
#include <imnodes.h>
#endif