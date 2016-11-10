cmake_minimum_required(VERSION 3.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

project(ColorGamutVisualization)

find_package(AntTweakBar REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLUT REQUIRED)

set(src
    src/color.cpp
    src/Munsell.cpp
    src/Wavelength.cpp
    src/sRGB.cpp
    src/KodakMinilab.cpp
    src/NormalizedXYZ.cpp
    src/XYZ.cpp
    src/transfm.c
    src/Lab.cpp
    src/SegmentMaximaColor.cpp
    src/main.cpp)

set(headers
    src/Color.h
    src/Lab.h
    src/SegmentMaximaColor.h
    src/XYZ.h
    src/transfm.h
    src/Defines.h
    src/Munsell.h
    src/Vec.h
    src/main.h
    src/KodakMinilab.h
    src/NormalizedXYZ.h
    src/Wavelength.h
    src/sRGB.h)

add_executable(gamut ${src} ${headers})
target_link_libraries(gamut ${ATB_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW3_LIBRARIES} ${GLEW_LIBRARIES})
