# Copyright (c) 2014 Fabian Schuiki
# CMake configuration file for the anium library.
cmake_minimum_required(VERSION 2.8)
project(anium)

install(DIRECTORY anium/ DESTINATION include/anium)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH})
find_package(Cairo)
find_package(GLFW)
find_package(OpenGL)

# Build the tests.
include_directories(.)
if (Cairo_FOUND)
	include_directories(${Cairo_INCLUDE_DIRS})
	add_executable(test-cairo test/cairo.cpp)
	target_link_libraries(test-cairo ${Cairo_LIBRARIES})
else()
	message(STATUS "Not building test-cairo (cairo library missing)")
endif()

add_executable(test-event test/event.cpp)

if (Cairo_FOUND AND GLFW_FOUND AND OPENGL_FOUND)
	include_directories(${Cairo_INCLUDE_DIRS})
	include_directories(${GLFW_INCLUDE_DIRS})
	include_directories(${OPENGL_INCLUDE_DIRS})
	add_executable(test-interactive test/interactive.cpp)
	target_link_libraries(test-interactive ${Cairo_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
	if (APPLE)
		target_link_libraries(test-interactive "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
	endif()
else()
	message(STATUS "Not building test-interactive (cairo or opengl library missing)")
endif()