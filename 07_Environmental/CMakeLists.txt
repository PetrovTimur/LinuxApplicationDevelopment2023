cmake_minimum_required(VERSION 3.22)
project(RHasher)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

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

enable_testing()

add_test(NAME test_file
	COMMAND "${CMAKE_CURRENT_LIST_DIR}/tests/test_file.sh")

add_test(NAME test_md5
	COMMAND "${CMAKE_CURRENT_LIST_DIR}/tests/test_md5.sh")

add_test(NAME test_sha1
	COMMAND "${CMAKE_CURRENT_LIST_DIR}/tests/test_sha1.sh")

add_custom_target(clear-all
	COMMAND git clean -qxdf
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)