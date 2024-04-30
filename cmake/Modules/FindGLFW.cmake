#
# Try to find the GLFW library and its include path.
#
# Once done, this will define the following:
#
# - GLFW_FOUND
# - GLFW_INCLUDE_DIR
# - GLFW_LIBRARIES
#
# Source: https://github.com/libigl/libigl-examples/blob/master/cmake/FindGLFW.cmake
#

if (NOT GLFW_FOUND)
	find_path(
		GLFW_INCLUDE_DIR
		GLFW/glfw3.h
		PATHS
			${PROJECT_SOURCE_DIR}/../../external/glfw/include
			${PROJECT_SOURCE_DIR}/../external/glfw/include
			${PROJECT_SOURCE_DIR}/external/glfw/include
			${PROJECT_SOURCE_DIR}/../../libigl/external/glfw/include
			${PROJECT_SOURCE_DIR}/../libigl/external/glfw/include
			${PROJECT_SOURCE_DIR}/libigl/external/glfw/include
			${PROJECT_SOURCE_DIR}/../../libigl/external/nanogui/ext/glfw/include
			${PROJECT_SOURCE_DIR}/../libigl/external/nanogui/ext/glfw/include
			${PROJECT_SOURCE_DIR}/libigl/external/nanogui/ext/glfw/include
			/usr/local/include
			/usr/X11/include
			/usr/include
			/opt/local/include
		NO_DEFAULT_PATH
	)

	message(STATUS "GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}") # TODO: Delete.

	find_library(
		GLFW_LIBRARIES
		NAMES
			glfw 
			glfw3
		PATHS
			${PROJECT_SOURCE_DIR}/../../external/glfw/src
			${PROJECT_SOURCE_DIR}/../external/glfw/src
			${PROJECT_SOURCE_DIR}/external/glfw/src
			${PROJECT_SOURCE_DIR}/../../libigl/external/glfw/src
			${PROJECT_SOURCE_DIR}/../libigl/external/glfw/src
			${PROJECT_SOURCE_DIR}/libigl/external/glfw/src
			${PROJECT_SOURCE_DIR}/../../external/glfw/lib/x64
			${PROJECT_SOURCE_DIR}/../external/glfw/lib/x64
			${PROJECT_SOURCE_DIR}/external/glfw/lib/x64
			${PROJECT_SOURCE_DIR}/../../libigl/external/glfw/lib/x64
			${PROJECT_SOURCE_DIR}/../libigl/external/glfw/lib/x64
			${PROJECT_SOURCE_DIR}/libigl/external/glfw/lib/x64
			/usr/local
			/usr/X11
			/usr
		PATH_SUFFIXES
			a
			lib64
			lib
		NO_DEFAULT_PATH
	)

	message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}") # TODO: Delete.

	set(GLFW_FOUND "NO")
	if (GLFW_INCLUDE_DIR AND GLFW_LIBRARIES)
		set(GLFW_FOUND "YES")
	endif (GLFW_INCLUDE_DIR AND GLFW_LIBRARIES)

	if (GLFW_FOUND)
		message(STATUS "Found GLFW: ${GLFW_INCLUDE_DIR}.")
	else (GLFW_FOUND)
		if (NOT GLFW_FIND_QUIETLY)
			message(FATAL_ERROR "Could not find GLFW.")
		endif (NOT GLFW_FIND_QUIETLY)
	endif (GLFW_FOUND)
endif (NOT GLFW_FOUND)
