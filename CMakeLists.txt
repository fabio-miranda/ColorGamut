cmake_minimum_required(VERSION 3.6)

project(ColorGamutVisualization)

# Prefer GLVND libraries for OpenGL and GLX.
cmake_policy(SET CMP0072 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(ANTTWEAKBAR REQUIRED) # https://anttweakbar.sourceforge.io/doc/
find_package(OpenGL REQUIRED) # https://www.mesa3d.org/
find_package(GLEW REQUIRED) # https://glew.sourceforge.net/
find_package(GLFW REQUIRED) # https://www.glfw.org/
find_package(GLUT REQUIRED) # https://freeglut.sourceforge.net/

set(
	src
	src/Color.cpp
	src/Munsell.cpp
	src/Wavelength.cpp
	src/sRGB.cpp
	src/KodakMinilab.cpp
	src/NormalizedXYZ.cpp
	src/XYZ.cpp
	src/transfm.c
	src/Lab.cpp
	src/SegmentMaximaColor.cpp
	src/main.cpp
)

set(
	headers
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
	src/sRGB.h
)

# TODO: Delete.
# get_cmake_property(_variableNames VARIABLES)
# list(SORT _variableNames)
# foreach (_variableName ${_variableNames})
# 	message(STATUS "${_variableName}=${${_variableName}}")
# endforeach ()

add_executable(gamut ${src} ${headers})
include_directories(${ANT_TWEAK_BAR_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(gamut ${ANT_TWEAK_BAR_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLUT_LIBRARIES})
