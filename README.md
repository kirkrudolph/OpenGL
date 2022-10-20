# OpenGL

Option 2 (GLFW)



## What is OpenGL

OpenGL is just a specification. Not a Library.
GPU manufacturer's drivers include OpenGL implement.
- Not open source.
- Cross platform (not optimal, native is usualy more powerful/better)
- Easier to learn (Vulcan is an alternative but newer)
- "Legacy" OpenGL started in 90's (think limited preset options)
- "Modern" OpenGL has more low-level control
    - Shader (Program that runs on GPU)

## Creating a Window
"Windowing" is very Platform specific (OS level thing)
- Windows: win32 API
- Linux: X11
- Mac: ?

GLFW (lightweight)
SDL (full framework)
wxWidgets (see KiCAD)

## Modern OpenGL
- GLFW: Window, run loop, process input, etc.
- GLAD or GLEW: Manages function pointers for "Modern" OpenGL
- OpenGL: Graphics API. Access GPU
    - Alternatives to OpenGL: Direct 3D (Windows), Vulcan (Cross Platform), Metal (MacOS)

Notes:
- I installed GLFW via `brew install glfw` but instead of using the dynamic library, I'm using a static library built from CMake and the glfw source code. The headerfile is from the brew install.


## Build
`Cmd+Shift+B`: Execute default build task in VSCode

## Run
`Cntr+Alt+T`: Run executable

or

```
./build/app
```

## Resources

- [Setup Tutorial](https://www.youtube.com/watch?v=7-dL6a5_B3I&t=3s)
- [GLFW Docs](https://www.glfw.org/documentation.html)
- [The Cherno](https://www.youtube.com/watch?v=OR4fNpBjmq8&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=2)