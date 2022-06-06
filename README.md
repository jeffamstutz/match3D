# match3D - a 3D viewer bootstrapping library

The match3D app prototyping library combines three ingredients: windowing
library ([GLFW](https://github.com/glfw/glfw)), UI library ([Dear
ImGui](https://github.com/ocornut/imgui)), and build system infrastructure
(CMake) to all but eliminate the boilerplate involved in making simple 3D
applications with a UI.

### Requirements

- CMake
- C++11 compiler
- GLFW

match3D is developed and tested on Linux, but has nothing inherently platform
specific in it. If you try it on macOS or Windows and find a problem, let
me know!

# Building with match3D

The match3D library is consumed as a source library. This is easiest to do
using CMake via the provided package config. The provided example (found in
[examples/simple](examples/simple)) is built like an external consumer of the
library.

The library is found by pointing your project's build to a local copy of the
`match3D` source with either `match3D_DIR` variable or appending it to
`CMAKE_PREFIX_PATH`. Then the consuming CMake is very straightforward and will
look something like:

```cmake
find_package(match3D REQUIRED)
add_executable(myApplication)
target_link_libraries(myApplication PRIVATE match3D::match3D)
```

Linking with the `match3D::match3D` target is all that is needed to bring in the
necessary includes and linked libraries to build your application, including
GLFW and Dear Imgui. Note that `find_package(match3D)` will require GLFW to be
found in your environment in order to succeed in finding match3D itself.

Downstream targets which link against `match3D::match3D` have everything
directly built into it.

### Using additional components

match3D can optionally bring in additional header-only libraries: currently
`stb_image` and `glm`. These are optionally added to the build by passing them
to `find_package` as components. For example, the following will also fetch
`glm` when constructing the match3D targets:

```cmake
find_package(match3D REQUIRED COMPONENTS glm)
```

Which then lets you include `glm` normally in your app:

```cpp
#include <glm/glm.hpp>
```

# Using the library to create an application

The match3D library revoles around a single C++ base class: `Application`.
This class has applications override methods to inject functionality for
creating the UI and drawing objects (with OpenGL) each frame. Specifically,
applications must override:

- `Application::setup()` -- this is invoked before the main UI loop is started
- `Application::buildUI()` -- where all ImGui calls are made to create the UI
- `Application::drawBackground()` -- where any drawing underneath the UI happens
- `Application::teardown()` -- cleanup to occur before the destructor

Each of the above methods are pure-virtual (`=0`) so that each customization
point is always visible in an implementation. The [provided
example](examples/simple/main.cpp) shows a minimal demonstration of an
application.

NOTE: all mouse and keyboard I/O is to be done through Dear ImGui -- see example
app to see it in action.

Window resize events are queried on each call to `buildUI()` via the protected
method `bool Application::getWindowSize(int &width, int &height)`. The method
always writes the width/height as out parameters and returns `true` if the
window has been resized since the last frame.

Finally, applications must create a simple `main()` function to instantiate and
run the application. This may look something like:

```c++
int main()
{
  MyMatch3DApp app;
  app.run(1280, 800, "Example match3D application");
}
```

The arguments provided to `Application::run()` are the initial window size and
title bar text.

# TODO

- [ ] mulitple windowing library options (SDL2, GLUT, etc.)
