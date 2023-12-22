cmake_minimum_required(VERSION 3.22)
project(Guesser)

find_package(Gettext)
find_package(Doxygen)

gettext_process_po_files(ru_RU.UTF-8 ALL
INSTALL_DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/locale
PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/locale/ru_RU.UTF-8/LC_MESSAGES/messages.po)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doxygen_doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
endif ()

add_executable(guess src/guess.c)

add_custom_command(OUTPUT guess.man
	COMMAND help2man $<TARGET_FILE:guess> -o guess.man
)

add_custom_target(GenerateMan ALL
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/guess.man
)