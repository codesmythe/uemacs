cmake_minimum_required (VERSION 3.10)

project (uemacs)

set (TARGET ue.tos)

set (SOURCES basic.c bind.c bindable.c buffer.c display.c ebind.c eval.c exec.c execute.c file.c fileio.c flook.c
        input.c isearch.c line.c lock.c main.c mlout.c names.c pklock.c posix.c random.c region.c search.c spawn.c
        tcap.c termio.c utf8.c util.c window.c word.c wrapper.c fridge/vt52.c)

add_executable(${TARGET} ${SOURCES})

target_compile_definitions(${TARGET} PUBLIC AUTOCONF)
target_compile_definitions(${TARGET} PUBLIC PROGRAM=ue)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Libcmini does not support unicode.
#target_include_directories(${TARGET} SYSTEM PUBLIC /Users/robg/libcmini/include)
#target_link_directories(${TARGET} PUBLIC /Users/robg/libcmini/lib)
#target_link_libraries(${TARGET} PUBLIC cmini gcc)
#target_link_options(${TARGET} PUBLIC -s -nostdlib /Users/robg/libcmini/lib/crt0.o)

target_compile_options(${TARGET} PUBLIC -std=c99 -O2 -pedantic -Wall -Wextra -Wstrict-prototypes -Wno-unused-parameter)


