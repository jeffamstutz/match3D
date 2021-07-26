// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#pragma once
// std
#include <stddef.h>
#include <memory>
#include <string_view>

namespace match {

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

  void run(size_t width, size_t height, const char *name);

 private:
  void mainLoop();

  std::shared_ptr<AppImpl> m_impl{nullptr};
};

} // namespace match