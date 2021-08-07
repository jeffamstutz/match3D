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

`match3D` is developed and tested on Linux, but has nothing inherently platform
specific in it. If you try it on `macOS` or `Windows` and find a problem, let
me know!

# Building against match3D

There are 2 methods for using match3D as a library, either as a source library
or as a pre-compiled binary library. Either method is easiest to use with CMake
via the provided package config. The provided example (found in
[example/external](example/external)) can be built with either method.

With either method, the consuming CMake is very straightforward and will look
something like:

```cmake
find_package(match3D REQUIRED)
add_executable(myApplication)
target_link_libraries(myApplication PRIVATE match3D::match3D)
```

The `match3D::match3D` target is all that is needed to bring in the necessary
includes and linked libraries to build your application, including GLFW and
Dear Imgui. Note that `find_package(match3D)` will require GLFW to be found in
your environment in order to succeed finding `match3D`.

## Usage as a source library

The first method of using `match3D` is treating a source tree as a CMake
package.  This is done by pointing CMake to a local copy of the `match3D` source
with either `match3D_DIR` variable or appending it to `CMAKE_PREFIX_PATH`.

This method creates `match3D::match3D` as an INTERFACE target, carrying with it
include paths and `.cpp` sources for the match3D library itself and ImGui.
Downstream targets which link against `match3D::match3D` have everything
directly built into it.

## Usage as a pre-compiled library

The second method of using `match3D` is a more traditional pre-built CMake
package.  This is done by first building `match3D` in a local build directory,
then installing it (destination specified with `CMAKE_INSTALL_PREFIX`). This
might look something like (installed to `~/opt/match3D`):

```
% mkdir build
% cd build
% cmake -DCMAKE_INSTALL_PREFIX=~/opt/match3D /path/to/match3D/source
% cmake --build . --target install
```

Then downstream consumers would then point their CMake build to the location
that `match3D` was installed, with either `match3D_DIR` directly or appending
`CMAKE_PREFIX_PATH` (above example would use "`~/opt/match3D`").

# Creating an application

The `match3D` library revoles around a single C++ base class: `Application`.
This class has applications override methods to inject functionality for
creating the UI and drawing objects (with OpenGL) each frame. Specifically,
applications must override:

- `Application::setup()` -- this is invoked before the main UI loop is started
- `Application::buildUI()` -- where all ImGui calls are made to create the UI
- `Application::drawBackground()` -- where any drawing underneath the UI happens
- `Application::teardown()` -- cleanup to occur before the destructor

Each of the above methods are pure-virtual (`=0`) so that each customization
point is always visible in an implementation. The [provided
example](example/main.cpp) shows a minimal demonstration of an application.

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
