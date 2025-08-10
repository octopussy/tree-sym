cmake_minimum_required(VERSION 3.31)
project(TreeSym)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        thirdparty/raylib/include
)

add_executable(TreeSym main.cpp
        trees.h
        tree_sym.h
        tree_sym.cpp)
target_link_libraries(
        TreeSym
        ${CMAKE_SOURCE_DIR}/thirdparty/raylib/lib/libraylib.a
        opengl32
        gdi32
        winmm
)
