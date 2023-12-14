cmake_minimum_required(VERSION 3.22)
project(Guesser)

find_package(Gettext)

gettext_process_po_files(ru_RU.UTF-8 ALL
INSTALL_DESTINATION ${CMAKE_CURRENT_LIST_DIR}/locale
PO_FILES ${CMAKE_CURRENT_LIST_DIR}/locale/ru_RU.UTF-8/LC_MESSAGES/messages.po)

add_executable(guess guess.c)