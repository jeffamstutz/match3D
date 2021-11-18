// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#pragma once
// std
#include <memory>
#include <string_view>

namespace match3D {

struct AppImpl;

class Application
{
 public:
  Application();
  virtual ~Application() = default;

  virtual void setup() = 0;
  virtual void buildUI() = 0;
  virtual void drawBackground() = 0;
  virtual void teardown() = 0;

  void run(int width, int height, const char *name);

 protected:
  bool getWindowSize(int &width, int &height) const;
  float getLastFrameLatency() const;

 private:
  void mainLoop();

  std::shared_ptr<AppImpl> m_impl{nullptr};
};

} // namespace match3D