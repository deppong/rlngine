cmake_minimum_required(VERSION 3.18)

project(rlengine)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(rlengine main.cpp)
if(MSVC)
    target_link_libraries(rlengine ${SDL2_LIBRARIES})
    target_compile_options(rlengine PRIVATE /W4)
else()
    target_link_libraries(rlengine ${SDL2_LIBRARIES} -ldl -lm)
    target_compile_options(rlengine PRIVATE -Wall -Wextra)
endif()
