cmake_minimum_required (VERSION 3.10)

# Can't use libcmini as does not support unicode.

project (uemacs)

set (TARGET uemacs.tos)

set (SOURCES basic.c bind.c bindable.c buffer.c display.c ebind.c eval.c exec.c execute.c file.c fileio.c flook.c
        input.c isearch.c line.c lock.c main.c mlout.c names.c pklock.c posix.c random.c region.c search.c spawn.c
        tcap.c termio.c utf8.c util.c window.c word.c wrapper.c fridge/vt52.c)

add_executable(${TARGET} ${SOURCES})

target_compile_definitions(${TARGET} PUBLIC AUTOCONF)
target_compile_definitions(${TARGET} PUBLIC PROGRAM=uemacs)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${TARGET} PUBLIC -std=c99 -O2 -pedantic -Wall -Wextra -Wstrict-prototypes -Wno-unused-parameter)


