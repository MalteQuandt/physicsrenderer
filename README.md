This Project aims to be a simple rigid body physics engine/simulator supporting multiple-body simulations of simple polygons.

Aims of this project, in order of importance: 

- [ ] Creation of objects
- [ ] Load&store model for the vertices & shaders
- [ ] Rendering of objects
- [ ] Moving about the scene
- [ ] Render of simple grid structure
- [ ] Bare-Bones collision detection
- [ ] Bare-Bones physics simulation
- [ ] Creation of objects through imgui-overlay

### Dependencies

**BEWARE**: As this Project depends on *multiple* external libraries, the first run of cmake will take a while!

This engine makes use of the following external libraries:

| Library          | Short Description                                  |
| ---------------- | -------------------------------------------------- |
| GLAD             | OpenGL Loader Library for the function pointers    |
| GLFW             | Window management system                           |
| DearImGui        | Immediate Mode gui library                         |
| GLM              | OpenGL Math Library                                |
| Assimp           | Model loading library                              |
| stb -> stb-image | general purpose, we only use the image loader here |

### Installation

#### Installation with Terminal

First, clone the project: 

> git clone https://github.com/MalteQuandt/physicsrenderer.git

Then, switch into that directory

> cd .\physicsrenderer\

Next, configure cmake (If you want it build for a certain build file type, add that with the ``-G`` flag at the end)

> cmake -S . -B .\build\ 

Build the project with 

> cmake --build .\build\ --target physics_renderer

And finally, run the application

> .\build\physics_renderer.exe

#### Installation with CLION

First, go to File -> New -> Project from Version Control, then input the remote git repository https://github.com/MalteQuandt/physicsrenderer.git and clone. After that is done, wait for a bit and after it has configured, start the building and run the project!

### Classes

- **Logger class**
  Logger utility that provides multiple logging channels for debugging purposes
- **State struct**
  Data class that contains all the state for the application, from the glfw window to the objects that are managed by this application
- **FileHandler**
  Utility class that handles file management
  - loadFileString


- **InputParser class**
  * Parse Command Line inputs 
  * Check, if option is set
  * Change startup state depending upon options
- **ShaderProgram class**
  * Create fragment & vertex shader
  * Link shader
  * Bind & unbind shader
  * Set shader options 
- **Camera class**
- **Overlay Renderer class**
- **2D support first, then 3d**
  - Renderer, that acts as a base class for either:
    * 2DRender, render unit that renders 2D
    * 3DRender, render unit that renders 3D
- **Entity class**
  An entity is an object in the world that has a position and all the other properties needed to accurately model it's physical behavior.
- **Scene Graph class**
- **Physics class**

### References

1. [GLFW Documentation](https://www.glfw.org/docs/latest/)
2. [DearImGui Introduction](https://blog.conan.io/2019/06/26/An-introduction-to-the-Dear-ImGui-library.html)
3. [Setting Up Glad CMake](https://github.com/Dav1dde/glad/issues/174)
3. [Learning Resource for OpenGL and basis for a few classes](https://learnopengl.com/)
3. [Assimp Documentation](http://assimp.sourceforge.net/lib_html/index.html)
3. [How to set up a model loader with assimp](https://learnopengl.com/Model-Loading/Assimp)
