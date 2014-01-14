# Copyright (c) 2014 Fabian Schuiki
# Try to find the GLFW library. If successful, the following will be defined:
#
# - GLFW_FOUND
# - GLFW_INCLUDE_DIRS
# - GLFW_LIBRARIES

include(LibFindMacros)

set(GLFW_PATHS
	$ENV{GLFW_DIR}
	${GLFW_DIR}
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt)

find_path(GLFW_INCLUDE_DIR
	NAMES GLFW/glfw3.h
	PATH_SUFFIXES include
	PATHS ${GLFW_PATHS})

find_library(GLFW_LIBRARY
	NAMES glfw3
	PATH_SUFFIXES lib
	PATHS ${GLFW_PATHS})

set(GLFW_PROCESS_INCLUDES GLFW_INCLUDE_DIR)
set(GLFW_PROCESS_LIBS GLFW_LIBRARY)
libfind_process(GLFW)