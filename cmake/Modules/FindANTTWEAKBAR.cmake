#
# Try to find the AntTweakBar library and its include path.
#
# Once done, this will define the following:
#
# - ANT_TWEAK_BAR_FOUND
# - ANT_TWEAK_BAR_INCLUDE_DIR
# - ANT_TWEAK_BAR_LIBRARY
#
# Source: https://github.com/libigl/libigl-examples/blob/master/cmake/FindANTTWEAKBAR.cmake.
#

if (WIN32)
	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(BITS "64")
	else (CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(BITS "")
	endif (CMAKE_SIZEOF_VOID_P EQUAL 8)

	find_path(
		ANT_TWEAK_BAR_INCLUDE_DIR
		AntTweakBar.h
		PATHS
			${PROJECT_SOURCE_DIR}/../../external/AntTweakBar/include
			${PROJECT_SOURCE_DIR}/../external/AntTweakBar/include
			${PROJECT_SOURCE_DIR}/external/AntTweakBar/include
			$ENV{ANT_TWEAK_BAR_ROOT}/include
		DOC "The directory where AntTweakBar.h resides"
	)

	find_library(
		ANT_TWEAK_BAR_LIBRARY
		AntTweakBar${BITS}
		PATHS
			${PROJECT_SOURCE_DIR}/../../external/AntTweakBar/lib
			${PROJECT_SOURCE_DIR}/../external/AntTweakBar/lib
			${PROJECT_SOURCE_DIR}/external/AntTweakBar/lib
			$ENV{ANT_TWEAK_BAR_ROOT}/lib
		DOC "The AntTweakBar library"
	)
else (WIN32)
	find_path(
		ANT_TWEAK_BAR_INCLUDE_DIR
		AntTweakBar.h
		PATHS
			${LIBIGL_INCLUDE_DIR}/../external/AntTweakBar/include/
			${PROJECT_SOURCE_DIR}/../../external/AntTweakBar/include/
			${PROJECT_SOURCE_DIR}/../external/AntTweakBar/include/
			${PROJECT_SOURCE_DIR}/external/AntTweakBar/include/
			/usr/local/include
			/usr/X11/include
			/usr/include
		NO_DEFAULT_PATH
	)

	find_library(
		ANT_TWEAK_BAR_LIBRARY
		AntTweakBar
		PATHS
			${LIBIGL_INCLUDE_DIR}/../external/AntTweakBar/lib
			${PROJECT_SOURCE_DIR}/../../external/AntTweakBar/lib
			${PROJECT_SOURCE_DIR}/../external/AntTweakBar/lib
			${PROJECT_SOURCE_DIR}/external/AntTweakBar/lib
			/usr/local
			/usr/X11
			/usr
		PATH_SUFFIXES
			a
			lib64
			lib
			dylib
		NO_DEFAULT_PATH
	)
endif (WIN32)

set(ANTTWEAKBAR_FOUND "NO")
if (ANT_TWEAK_BAR_INCLUDE_DIR AND ANT_TWEAK_BAR_LIBRARY)
	set(ANTTWEAKBAR_FOUND "YES")
endif (ANT_TWEAK_BAR_INCLUDE_DIR AND ANT_TWEAK_BAR_LIBRARY)

set(ANT_TWEAK_BAR_INCLUDE_DIR ${ANT_TWEAK_BAR_INCLUDE_DIR} ${ANT_TWEAK_BAR_INCLUDE_DIR}/../src/)

if (ANT_TWEAK_BAR_INCLUDE_DIR AND ANT_TWEAK_BAR_LIBRARY)
	message(STATUS "Found ANTTWEAKBAR: ${ANT_TWEAK_BAR_INCLUDE_DIR}.")
else (ANT_TWEAK_BAR_INCLUDE_DIR AND ANT_TWEAK_BAR_LIBRARY)
	if (NOT ANTTWEAKBAR_FIND_QUIETLY)
		message(FATAL_ERROR "Could not find ANTTWEAKBAR.")
	endif (NOT ANTTWEAKBAR_FIND_QUIETLY)
endif (ANT_TWEAK_BAR_INCLUDE_DIR AND ANT_TWEAK_BAR_LIBRARY)

file(GLOB ANT_TWEAK_BAR_SOURCES ${ANT_TWEAK_BAR_INCLUDE_DIR}/../src/*.c ${ANT_TWEAK_BAR_INCLUDE_DIR}/../src/*.cpp)
