// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Window.h"
// std
#include <memory>
#include <string_view>
#include <vector>

namespace match3D {

struct DockingAppImpl;

class DockingApplication
{
 public:
  DockingApplication();
  virtual ~DockingApplication() = default;

  virtual WindowArray setup() = 0;
  virtual void buildMainMenuUI() = 0;
  virtual void teardown() = 0;

  void run(int width, int height, const char *name);

 protected:
  bool getWindowSize(int &width, int &height) const;
  float getLastFrameLatency() const;

 private:
  void mainLoop();

  std::shared_ptr<DockingAppImpl> m_impl;
};

} // namespace match3D
