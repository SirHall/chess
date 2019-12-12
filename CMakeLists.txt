cmake_minimum_required(VERSION 3.7)

project(proj_out)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unknown-pragmas -Wno-unused-parameter -Iinclude -O3 -ffast-math -flto -lncurses)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS
"src/*.cpp"
RELATIVE_PATH
)

set(CMAKE_CXX_STANDARD 17)
add_executable(out ${SRCS})
target_include_directories(out PUBLIC ${INCLUDE_DIR})
target_link_libraries(out ${CURSES_LIBRARIES})