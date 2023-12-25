cmake_minimum_required(VERSION 3.22)
project(Guesser)

find_package(Gettext)
find_package(Doxygen)

gettext_process_po_files(ru_RU.UTF-8 ALL
INSTALL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/locale
PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/locale/ru_RU.UTF-8/LC_MESSAGES/messages.po)

set(TEXT_DOMAIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/locale)

cmake_path(RELATIVE_PATH TEXT_DOMAIN_DIR
           BASE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doxygen_doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
endif ()

add_compile_definitions(guess TEXTDOMAINDIR="${TEXT_DOMAIN_DIR}")
add_executable(guess src/guess.c)

add_custom_command(OUTPUT guess.man
	COMMAND help2man $<TARGET_FILE:guess> -o guess.man
)

add_custom_target(GenerateMan ALL
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/guess.man
)