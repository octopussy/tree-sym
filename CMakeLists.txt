cmake_minimum_required(VERSION 3.31)
project(TreeSym)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GoogleTest)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/244cec869d12e53378fa0efb610cd4c32a454ec8.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if (UNIX AND APPLE)
    message("OS: MacOS")
    #    set_target_properties(${name} PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")
    set(APP_LIBS
            ${CMAKE_SOURCE_DIR}/thirdparty/raylib/lib/macos/libraylib.a
            "-framework CoreVideo"
            "-framework IOKit"
            "-framework Cocoa"
            "-framework GLUT"
            "-framework OpenGL"
    )
elseif (UNIX)
    message("OS: Unix")
elseif (MINGW)
    message("OS: MinGW")
    set(APP_LIBS
            ${CMAKE_SOURCE_DIR}/thirdparty/raylib/lib/windows/libraylib.a
            opengl32
            gdi32
            winmm
    )
endif ()

include_directories(
        thirdparty/raylib/include
)

function(add_app name sources)
    add_executable(${name} ${sources})
    target_link_libraries(${name} ${APP_LIBS})
endfunction()

add_app(TreeSym
        main.cpp
        tree_sym.cpp
)

add_app(App2
        app2_main.cpp

)

enable_testing()
add_executable(
        t2_tests
        t2_parser_test.cpp
)
target_link_libraries(
        t2_tests
        GTest::gtest_main
)
gtest_discover_tests(t2_tests)
