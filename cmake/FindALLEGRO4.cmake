# - Find ALLEGRO4 includes and library
#
# This module defines
#  ALLEGRO4_INCLUDE_DIRS
#  ALLEGRO4_LIBRARIES, the libraries to link against to use ALLEGRO4.
#  ALLEGRO4_LIBRARY_DIRS, the location of the libraries
#  ALLEGRO4_FOUND, If false, do not try to use ALLEGRO4
#
# Copyright © 2016 Horgeon
# Based on a CMake script by Matt Williams
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

IF (ALLEGRO4_LIBRARIES AND ALLEGRO4_INCLUDE_DIRS)
	SET(ALLEGRO4_FIND_QUIETLY TRUE)
ENDIF (ALLEGRO4_LIBRARIES AND ALLEGRO4_INCLUDE_DIRS)

SET(ALLEGRO4_INCLUDE_SEARCH_DIRS
	"${INCLUDE_SEARCH_DIRS}"
	"${CMAKE_INCLUDE_PATH}"
	"/usr/include"
	"/usr/local/include"
	"/usr/include/allegro"
	"/usr/local/include/allegro"
	CACHE STRING ""
)

SET(ALLEGRO4_LIBRARY_SEARCH_DIRS
	"${LIBRARY_SEARCH_DIRS}"
	"${CMAKE_LIBRARY_PATH}"
	"/usr/lib"
	"/usr/lib64"
	"/usr/local/lib"
	"/usr/local/lib64"
	"/opt/lib"
	"/opt/lib64"
	CACHE STRING ""
)

IF (NOT ALLEGRO4_FIND_QUIETLY)
	MESSAGE(STATUS "Looking for Allegro 4")
ENDIF (NOT ALLEGRO4_FIND_QUIETLY)
FIND_PATH(ALLEGRO4_INCLUDE_DIRS allegro.h ${ALLEGRO4_INCLUDE_SEARCH_DIRS})
MESSAGE(STATUS "ALLEGRO4_INCLUDE_DIRS: " ${ALLEGRO4_INCLUDE_DIRS})

FIND_LIBRARY(Z_LIBRARY z)
SET(ALLEGRO4_LIBRARIES ${Z_LIBRARY})

FIND_LIBRARY(LOADPNG_LIBRARY loadpng)
LIST(APPEND ALLEGRO4_LIBRARIES ${LOADPNG_LIBRARY})

FIND_LIBRARY(PNG_LIBRARY png)
LIST(APPEND ALLEGRO4_LIBRARIES ${PNG_LIBRARY})

FIND_LIBRARY(JPGALLEG_LIBRARY jpgalleg)
LIST(APPEND ALLEGRO4_LIBRARIES ${JPGALLEG_LIBRARY})

FIND_LIBRARY(ALLEGROGL_LIBRARY alleggl)
LIST(APPEND ALLEGRO4_LIBRARIES ${ALLEGROGL_LIBRARY})

FIND_LIBRARY(ALLEGRO_LIBRARY alleg)
LIST(APPEND ALLEGRO4_LIBRARIES ${ALLEGRO_LIBRARY})

#Do some preparation

SET(ALLEGRO4_INCLUDE_DIRS ${ALLEGRO4_INCLUDE_DIRS})
SET(ALLEGRO4_LIBRARIES ${ALLEGRO4_LIBRARIES})
SET(ALLEGRO4_LIBRARY_DIRS ${ALLEGRO4_LIBRARY_DIRS})

MARK_AS_ADVANCED(ALLEGRO4_INCLUDE_DIRS ALLEGRO4_LIBRARIES ALLEGRO4_LIBRARY_DIRS)

IF (ALLEGRO4_INCLUDE_DIRS AND ALLEGRO4_LIBRARIES)
	SET(ALLEGRO4_FOUND TRUE)
ENDIF (ALLEGRO4_INCLUDE_DIRS AND ALLEGRO4_LIBRARIES)

IF (ALLEGRO4_FOUND)
	IF (NOT ALLEGRO4_FIND_QUIETLY)
		MESSAGE(STATUS "  libraries : ${ALLEGRO4_LIBRARIES} from ${ALLEGRO4_LIBRARY_DIRS}")
		MESSAGE(STATUS "  includes  : ${ALLEGRO4_INCLUDE_DIRS}")
	ENDIF (NOT ALLEGRO4_FIND_QUIETLY)
ELSE (ALLEGRO4_FOUND)
	MESSAGE(STATUS "allegro 4 not found!")
	IF (ALLEGRO4_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Allegro 4. Make sure you have the Allegro 4 development headers are installed. Otherwise, try setting LIBRARY_SEARCH_DIRS and INCLUDE_SEARCH_DIRS to the place Allegro 4 was installed with -DLIBRARY_SEARCH_DIRS=<path/to/lib> -DINCLUDE_SEARCH_DIRS=<path/to/include>")
	ENDIF (ALLEGRO4_FIND_REQUIRED)
ENDIF (ALLEGRO4_FOUND)