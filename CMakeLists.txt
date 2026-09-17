cmake_minimum_required(VERSION 3.20)

project(systemi VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(systemi ${SOURCES})

target_include_directories(systemi
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_options(systemi
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)
target_compile_definitions(systemi PRIVATE _POSIX_C_SOURCE=200809L)