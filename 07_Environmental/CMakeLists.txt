cmake_minimum_required(VERSION 3.22)
project(RHasher)


option(USE_READLINE "Use readline function" ON)
if (USE_READLINE)
	add_definitions(-DUSE_READLINE)	
endif (USE_READLINE)


find_library(RHASH_LIB rhash REQUIRED)
set(LIBS ${RHASH_LIB})

if(USE_READLINE)
	find_library(READLINE_LIB readline)
	if(NOT READLINE_LIB)
		message("-- Detecting readline lib - missing")
	else()
		list(APPEND LIBS ${READLINE_LIB})
		message("-- Detecting readline lib - done")
	endif()
else()
	message("-- Detecting readline lib - skipped")
endif()

add_executable(rhasher rhasher.c)
target_link_libraries(rhasher ${LIBS})