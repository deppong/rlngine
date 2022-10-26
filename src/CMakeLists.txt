cmake_minimum_required(VERSION 3.18)

project(rlngine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} .)

add_executable(rlngine 
    main.cpp 
    game.cpp 
    atlas.cpp
    color.cpp
    world.cpp
    zone.cpp
    json.cpp
    entity_factory.cpp
    ui.cpp
)

if(MSVC)
    target_link_libraries(rlngine ${SDL2_LIBRARIES})
    target_compile_options(rlngine PRIVATE /W4)
else()
    target_link_libraries(rlngine ${SDL2_LIBRARIES} -ldl -lm)
    target_compile_options(rlngine PRIVATE -Wall -Wextra)
endif()
