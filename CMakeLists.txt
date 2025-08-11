cmake_minimum_required(VERSION 3.31)
project(TreeSym)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        thirdparty/raylib/include
)

function(add_app name sources)
    add_executable(${name} ${sources})
    target_link_libraries(
            ${name}
            ${CMAKE_SOURCE_DIR}/thirdparty/raylib/lib/libraylib.a
            opengl32
            gdi32
            winmm
    )
endfunction()

add_app(TreeSym
        main.cpp
        tree_sym.cpp)

add_app(App2
        app2_main.cpp
)

