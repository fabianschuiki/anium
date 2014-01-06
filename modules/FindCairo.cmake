# Copyright (c) 2014 Fabian Schuiki
# Try to find the cairo library. If successful, the following will be defined:
#
# - Cairo_FOUND
# - Cairo_INCLUDE_DIRS
# - Cairo_LIBRARIES

include(LibFindMacros)

set(Cairo_PATHS
	$ENV{Cairo_DIR}
	${Cairo_DIR}
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt)

find_path(Cairo_INCLUDE_DIR
	NAMES cairo/cairo.h
	PATH_SUFFIXES include
	PATHS ${Cairo_PATHS})

find_library(Cairo_LIBRARY
	NAMES cairo
	PATH_SUFFIXES lib
	PATHS ${Cairo_PATHS})

set(Cairo_PROCESS_INCLUDES Cairo_INCLUDE_DIR)
set(Cairo_PROCESS_LIBS Cairo_LIBRARY)
libfind_process(Cairo)