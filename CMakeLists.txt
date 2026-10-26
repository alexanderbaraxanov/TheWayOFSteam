cmake_minimum_required(VERSION 3.8...4.2)
project(sfml-test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Window Graphics System REQUIRED)

add_executable(
    app 
    src/main.cpp
    src/Game/Game.cpp
    src/Player/Player.cpp
    src/Shape/Shape.cpp 
    src/Map/Map.cpp 
)

target_link_libraries(app PRIVATE SFML::Window SFML::Graphics SFML::System)