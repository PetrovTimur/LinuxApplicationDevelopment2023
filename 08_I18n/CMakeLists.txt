cmake_minimum_required(VERSION 3.22)
project(Guesser)

find_package(Gettext)

gettext_process_po_files(ru_RU.UTF-8 ALL
INSTALL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/locale
PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/locale/ru_RU.UTF-8/LC_MESSAGES/messages.po)

set(TEXT_DOMAIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/locale)

cmake_path(RELATIVE_PATH TEXT_DOMAIN_DIR
		   BASE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_compile_definitions(guess TEXTDOMAINDIR="${TEXT_DOMAIN_DIR}")
add_executable(guess guess.c)