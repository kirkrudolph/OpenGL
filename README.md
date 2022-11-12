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
- How to render something that is fully or partially transparent
- Blending determins how we combine our output color with what is already in the buffer
- Output = the color output from the fragment shader (known as the source)
- Target buffer = buffer that the fragment shader is drawing to (known as destination)
- Three ways to control:
1. glEnable(GL_BLEND), glDisable(GL_BLEND)
2. glBlendFunc(src, dest)
3. glBlendEquation(mode)

## 19 Math in OpenGL
- Vectors can be direction and/or position in 2D, 3D, 4D space
- `glm` is a good library for OpenGL. Efficient ordering. Header only.
- Model View Projection (MVP) matrix via shader

## 20 Projection Matrices
- Projection maps to [-1, 1] regardless of screen size
- Orthographic Projection: Usually 2D, UI
- Perspective Projection: Usually 3D, 1st person shooter

## 21 Model View Projection Matrices
- Model View Projections (MVP) Matrix
- Each is a 4x4 matrix.
- View Matrix is "view of camera"
- Model is the vertex of the object we're drawing
- Projection (see 20) maps into screen space
- Translation, Rotation, Scale (TRS)
- Multiplication is in reverse order. Memory layout is column major.
- OpenGL Matrix multiplication is right to left because of the way it expects it in the shader

## 22 ImGui in OpenGL
- GUI library
- Can be used with OpenGL, Direct X, or any rendering API. 
- Draw UI (buttons, text fields, color pickers, windows, debug, real-time rendering, etc.)
- Lightweight Qt or wpf alternative.
- Super cool. Not that hard to implement. Very good examples.

## 23 Rendering Multiple Objects
- Multiple ways to do it.
1. Have a second index buffer
2. Use a different MVP matrix on the same data.

Here, we used two MVP matrix transforms because we only have one object and just want to render it twice.

Not the best way for everything. Don't create a 2D tile layout via 1000 draw calls in a for loop. Instead, a tile map could be created in a single draw call via batching. Batching shoves all indexes into a single vertex buffer. Then change vertex positions in the single verterx buffer and render everything all in one go. Much faster than binding a shader, changing the uniform, and a draw call for a thousand individual tiles.

2D rendering, batching is a must. 
3D rendering of objects that are super complex, the method used here probably makes sense.

Material = shader + uniforms

## 24 Test Framework
- Goal is to clean up main function.
- Use ImGui to launch, execute, and close mini examples

## 25 Creating Tests
- Creating a test menu.

## 26 Creating a Texture Test
- Added back all code needed to render textures in a new test option.

## 27 Faster Uniforms
- Instead of retrieving uniforms from openGL every time we need to set a uniform
- Many things we can do to retain that location
- Once we've compiled the shader and that object lives on the GPU
- Shader in the GPU is aware of all the valid uniforms within it
- No reason to continously ask GPU "where is my uniform?"
- Any OpenGL call is going to be slower than any C++ style call
- Talk about Caching the uniform

What typically happens:
- Shader is compiled
- Game/Render engine reads shader source code
- Determines what to do with shader. Extract data. Find atributes, find uniforms

Today, add a quick and dirty hack to speed things up a bit.
- Actually, this was already done in the episode where we created the shader class.
- See `Shader.cpp -> GetUniformLocation` function.
    - Only uses `glGetUniformLocation` when uniform isn't already in buffer.

## 28 Batch Rendering - Introduction
- How to render more than one piece of geometry in a single draw call
- To date:
    - Build vertex buffer of vertexies
    - An index buffer with indices
    - Render with `gldrawelements`
    - Repeat for any object (ex new square or rectagnle)
- Can reuse the same vertex and index buffer if geometry doesn't change
    - Use uniform matrix in vertex shader to position/transform that piece of geometry
- What happens if we want to render a lot of things? Huge amount of geometry?
- This video specifically for 2D batching. Ignoring 3D batching.
- How to render many 2D rectangles? 

Example:
    - 2D top down RPG. World is made of tiles (think pokemon)
        - Poor performance if 100's or 1000's of individual draw calls.
        - GPU can't keep up.
        - Modern desktop with dedicated GPUs can do 1000's of draw calls.
        - Bigger issue for old hardware or mobile.
    - Particle system
        - Fire particles
        - Smoke particles
        - [Example video](https://www.youtube.com/watch?v=qITIvVV6BHk): Individual quads with transforms
    - UI rendering
        - Text on the screen.
        - Quest journal entry with paragraphs of text.
        - Each character is a seperate texture quad.
        - 1000's of text characters.

Batch rendering enables above examples without huge performance hit.
Batch together all the geometry into a single vertex/index buffer and draw once. (instead of everything individual)
Colors would also exist in vertex buffer

Vertex Array                                    -----
- Vertex Buffer -> 4 Vertices [0,1,2,3]         |  /|
- Index Buffer -> 6 Indices   [0,1,2;0,2,3]     |/  |
- Transform to make two.                        -----

Batched Vertex Array                            -----   -----
- Vertex Buffer -> 8 Vertices   [0:7]           |  /|   |  /|
- Index Buffer -> 12 Indices    []              |/  |   |/  |
                                                -----   -----

Upside
- Fast
Downside
- Can't use transform to set position. Has to be done in vertex buffer.

## 29 Batch Rendering - Colors
- Colors, Texture, Dynamically change quads being drawn, etc.

Add color attribute to vertex buffer (instead of just positions).



## 30 Batch Rendering - Textures

## 31 Batch Rendering - Dynamic Geometry

Notes:
- I installed GLFW via `brew install glfw` but instead of using the dynamic library, I'm using a static library built from CMake and the glfw source code. The headerfile is from the brew install.

## Resources

- [GLFW Docs](https://www.glfw.org/documentation.html)
- [The Cherno](https://www.youtube.com/watch?v=OR4fNpBjmq8&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=2)
- [OpenGL API](https://docs.GL)
