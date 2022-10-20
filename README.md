# GLFW App

Option 1 (see kicad)
- wxWidgets

Option 2 (GLFW)

- GLFW: Window, run loop, process input, etc.
- GLAD or GLEW: Manages function pointers for OpenGL


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