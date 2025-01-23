cmake_minimum_required(VERSION 3.27)
project(less4c C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

macro(load_files name)
    if (${ARGC} GREATER 1)
        set(paths ${ARGN})
    else ()
        set(paths inc src)
    endif ()
    set(target_files)
    foreach (path ${paths})
        file(GLOB_RECURSE files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${path} *.h *.c)
        foreach (file ${files})
            if (NOT ${file} MATCHES "^\\..*$")
                list(APPEND target_files ${path}/${file})
            endif ()
        endforeach ()
    endforeach ()
    set(${name} ${target_files})
endmacro()

load_files(LIB_SOURCES)

add_library(less4c SHARED ${LIB_SOURCES})

include_directories(.)
enable_testing()
add_subdirectory(test)
