# ColorGamut

[Color gamut visualization](https://fmiranda.me/projects/color-gamut/).

Interactive visualization of different sets of colors (all visible colors, sRGB, Munsell) on three different color spaces: CIE XYZ, CIELAB, and sRGB. Segment Maxima Method for computing gamut boundary based on Morovic et al., 2000.

## Dependencies

This project depends on the following libraries:

- [AntTweakBar](https://anttweakbar.sourceforge.io/doc/).
- OpenGL (can be satisfied by [Mesa 3D](https://www.mesa3d.org/)).
- [GLEW](https://glew.sourceforge.net/).
- [GLFW](https://www.glfw.org/).
- GLUT (can be satisfied by [freeglut](https://freeglut.sourceforge.net/))

### AntTweakBar

Follow [the instructions on the AntTweakBar website](https://anttweakbar.sourceforge.io/doc/tools_anttweakbar_download.html) to build the library, then place the `AntTweakBar` folder inside of `ColorGamut/external` such that `ColorGamut/external/AntTweakBar/include/AntTweakBar.h` exists.

### OpenGL

Install an implementation of OpenGL. On Ubuntu, this means installing Mesa 3D:

```bash
sudo apt install libglu1-mesa-dev
```

### GLEW

Install GLEW. On Ubuntu:

```bash
sudo apt install libglew-dev
```

### GLFW

Follow [the instructions on the GLFW website](https://www.glfw.org/docs/latest/compile.html) to build the library, ensuring that the root directory and the build directory are the same, then place the `glfw` folder inside of `ColorGamut/external` such that `ColorGamut/external/glfw/include/GLFW/glfw3.h` exists.

### GLUT

Install GLEW. On Ubuntu, this means installing freeglut:

```bash
sudo apt install freeglut3-dev
```

## Steps to Build

1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

The executable will be exported as `ColorGamut/build/gamut`. Make sure that you copy the files in the `data` folder into the same directory as the executable before running the program.
