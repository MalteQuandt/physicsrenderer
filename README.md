This Project aims to be a simple rigid body physics engine/simulator supporting multiple-body simulations of simple polygons.

Aims of this project, in order of importance: 

1. Rendering of objects
2. Creation of objects
3. Bare-Bones collision detection
4. Bare-Bones physics simulation
5. Creation of objects through imgui-overlay
6. Dynamic loading of resources and shaders

### Dependencies

**BEWARE**: As this Project depends on *multiple* external libraries, so the first run of cmake will take a while!

This engine makes use of the following external libraries:

| Library   | Short Description                               |
| --------- | ----------------------------------------------- |
| GLAD      | OpenGL Loader Library for the function pointers |
| GLFW      | Window management system                        |
| DearImGui | Immediate Mode gui library                      |

### Installation

#### Installation with Terminal

First, clone the project: 

> git clone https://github.com/MalteQuandt/physicsrenderer.git

Then, switch into that directory

> cs .\physicsrenderer\

Next, configure cmake (If you want it build for a certain build file type, add that with the ``-G`` flag at the end)

> cmake -S . -B .\build\ 

Build the project with 

> cmake --build . --target physics_renderer

And finally, run the application

> .\build\physics_renderer.exe

#### Installation with CLION

First, go to File -> New -> Project from Version Control, then input the remote git repository https://github.com/MalteQuandt/physicsrenderer.git and clone. After that is done, wait for a bit and after it has configured, start the building and run the project!

### References

1. [GLFW Documentation](https://www.glfw.org/docs/latest/)
2. [DearImGui Introduction](https://blog.conan.io/2019/06/26/An-introduction-to-the-Dear-ImGui-library.html)
3. [Setting Up Glad CMake](https://github.com/Dav1dde/glad/issues/174)
