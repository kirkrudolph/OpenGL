# OpenGL

## Build
`Cmd+Shift+B`: Execute default build task in VSCode

## Run
`Cntr+Alt+T`: Run executable

or

```
./build/app
```

## 1. Welcome to OpenGL

OpenGL is:
- Just a specification. (similar to c/c++ language specification)
- Cross platform (not optimal, native is usualy more powerful/better)
- Easier to learn (Vulcan is an alternative but newer)

OpenGL is not:
- open source (GPU manufacturer's drivers include OpenGL implementation)
- a library (no code to include, compile, link, etc.)

OpenGL history:
- "Legacy" OpenGL (v1) started in 90's (think limited preset options)
- "Modern" OpenGL (v2-v4) has more low-level control of GPU

## 2. Setting up OpenGL and Creating a Window

- [Setup Tutorial (Mac)](https://www.youtube.com/watch?v=7-dL6a5_B3I&t=3s)

"Windowing" is very Platform specific (OS level thing)
- Windows: win32 API
- Linux: X11
- Mac: ?

Cross-Platform options for windowing:
- GLFW 
    - lightweight
    - used in this example
- SDL 
    - full framework
- wxWidgets
    - see KiCAD as example

## 3. Modern OpenGL
- GLFW: Window, run loop, process input, etc.
- GLAD or GLEW: Manages function pointers for "Modern" OpenGL
    - Extracts available functions from your GPU
- OpenGL: Graphics API. Access GPU
    - Alternatives to OpenGL: Direct 3D (Windows), Vulcan (Cross Platform), Metal (MacOS)
- Two steps
    - Create Vertex Buffer: Array of data that lives on the GPU
    - Shader: Code that runs on GPU for how to use data
- OpenGL is a state machine. Standard workflow:
    - Select vertex buffer (Give GPU data)
    - Select Shader (Program to execute)
    - Draw Object (Actual Execution)

## 4. Vertex Buffers and Drawing a Triangle

## 5. Vertex Attributes and Layouts

## 6. How Shaders Work

Two primary types: Vertex, Fragment (pixel) shaders. But many other types: Geometry, Compute, etc.

(Simplified) Order
1. Draw Call
2. Vertex Shader (Called for each vertex. Example) Triangle has three calls)
    - Can pass data from Vertex Shader to Fragment Shader
3. Fragment Shader (Run once for each pixel that needs to be drawn (i.e. thousands). Mainly color)
    - Example is lighting. Env, texture, lighting, material, camera, etc come together to determine color
4. Result on screen

- 80-90% in these two shaders. 
- Really good graphics can be 1000s of lines of code in a shader.
- Game engines generate shaders on the fly based on settings, context, etc.

## 7 & 8 Writing a Shader in OpenGL
- Added shader code.
- Import Shader code from other file.

## 9 Index Buffers
- Triangles are the GPUs basic building block
- Example: draw a square with 4 unique points instead of 6 points (3 for triangle 1 and 3 for triangle 2)
- Vertex buffer, index buffer, DrawElements is what's used 90% of the time (even AAA games).

## 10 Dealing With Errors
`glGetError` - fully compatible because it's been around from the begining
`glDebugMessageCallback` - newer function (only available in v4.3+)
Standard Workflow
1. Clear all errors (call in a loop to clear all errors)
2. Call GL function
3. Call glGetError again

Created macros for error checking.

## 11 Uniforms in OpenGL
Uniforms are a way to get data from CPU into shader for use as a variable
- alternative to attributes already used
- uniforms are set per draw (i.e. can't use this to make two triangles different colors)
- attributes are set per vertex

## 12 Vertex Arrays
- Unique to OpenGL (doesn't exist in other graphic APIs)
- Binds vertex buffer with layout of data in that buffer
- If you use "core" profile, you have to make a vertex array object (vao).
- If you use the "compatability" profile, there is a default vao bound and setup already for use.
- Two Options:
    1. One global vao. Create a "default" vertex array object (vao) and leave it bound for the duration of the program. Then you can bind the vertex buffer and specify the vertex layout every time before drawing. Basically
    the same as using the compatability profile.
    2. One vao for each object. For every piece of geometry, create a vao. When it comes time to draw, bind a new vao every time.
- Which is better? 
    - Nvidia had a paper that "One vao is better" (performance wise)
    - OpenGL recommends using multiple vao's.
    - Very enviornment dependant. Probably need to benchmark if needing every bit of performance.
We'll use multiple vaos.

## 13 Vertex and Inex Buffer Classes
- Reorganizing code.

## 14 Vertex Array Abstraction
- Lots of code changes

## 15 Shader Abstraction
- Shader generation at run-time is common.
- Abstracting shaders can be very, very complex.

## 16 Renderer
- Contains draw call.
- Debate of should multiple instances be allowed.

## 17 Textures
- Basic Idea: Image from photoshop, paint, etc. on the surface in the application.
- Can be as complicated as adjusting textures via lighting effects (I think he's refering to ray casting).

1. Load image into CPU memory. (this example uses a .png)
- Most game engines use their own texture format
- Use library to give file path and recieve a buffer of rgba pixels

- OpenGL has multiple "slots" to bind textures at the same time.
    - modern GPUs have ~32 texture slots
    - mobile (Apple, Android) might have like ~8 texture slots
    - can ask OpenGL for the number on the platform

- OpenGL expects texture pixels to start at the bottom left (not top left)
- Depends on texture formats but png starts at top left.

- Resampling/scaling/filtering images is a big deal. Lots of settings and options.
- Internal format is how OpenGL stores texture data.
- Format is the data you're providing OpenGL with

- Need to tell shader which texture slot to sample from
- Integer Uniform "sampler slot"

- Need to add texture coordinates

- Send data from vertex shader to fragment shader with a "vary"

## 18 Blending in OpenGL

## 19 Math in OpenGL

## 20 Projection Matrices

## 21 Model View Projection Matrices

## 22 ImGui in OpenGL

## 23 Rendering Multiple Objects

## 24 Test Framework

## 25 Creating Tests

## 26 Creating a Texture Test

## 27 Faster Uniforms

## 28 Batch Rendering - Introduction

## 29 Batch Rendering - Colors

## 30 Batch Rendering - Textures

## 31 Batch Rendering - Dynamic Geometry

Notes:
- I installed GLFW via `brew install glfw` but instead of using the dynamic library, I'm using a static library built from CMake and the glfw source code. The headerfile is from the brew install.

## Resources

- [GLFW Docs](https://www.glfw.org/documentation.html)
- [The Cherno](https://www.youtube.com/watch?v=OR4fNpBjmq8&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=2)
- [OpenGL API](https://docs.GL)
