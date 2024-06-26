cmake_minimum_required(VERSION 3.28)
set(PROJECT_NAME "GameOfLife")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

# Replace this path with the path to your Raylib installation
list(APPEND CMAKE_PREFIX_PATH "/path/to/your/raylib")

find_package(raylib 3.0 QUIET) # Let's find the installed raylib

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp
        include/grid.h
        src/grid.cpp
        include/simulation.h
        src/simulation.cpp
        include/raygui.h
        include/application.h
        src/application.cpp
        include/menu.h
        src/menu.cpp
        include/application-specification.h
        src/raygui.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} raylib)