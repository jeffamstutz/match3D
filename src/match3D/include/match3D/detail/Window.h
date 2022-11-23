// Copyright 2021 Jefferson Amstutz
// SPDX-License-Identifier: Apache-2.0

#pragma once

// std
#include <memory>
#include <string>
#include <vector>

namespace match3D {

struct Window
{
  Window(const char *name, bool startShown = false, bool wrapBeginEnd = true);
  virtual ~Window() = default;

  void renderUI();

  void show();
  void hide();
  void toggleShown();

  bool *visiblePtr();
  const char *name();

  virtual int windowFlags() const;

 protected:
  virtual void buildUI() = 0;

 private:
  std::string m_name;
  bool m_visible{false};
  bool m_wrapBeginEnd{true};
};

using WindowArray = std::vector<std::unique_ptr<Window>>;

} // namespace match3D
