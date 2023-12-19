set(TESTS_SOURCES
	InitTest.c
	NullTest.c
	PushTest.c
	GrowTest.c
	PopTest.c
)

foreach(TEST_SOURCE ${TESTS_SOURCES})
	cmake_path(GET TEST_SOURCE STEM TEST)

	add_executable(${TEST} ${TEST_SOURCE} test.h)
	target_link_libraries(${TEST} Buf)

	target_include_directories(${TEST} PUBLIC
                          	  "${PROJECT_SOURCE_DIR}"
                          	  )

    add_test(NAME ${TEST}
    		 COMMAND ${TEST}
    		)

	message("Added test: ${TEST}")
endforeach()