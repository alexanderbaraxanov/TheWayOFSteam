cmake_minimum_required(VERSION 3.8...4.2)
project(sfml-test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Window Graphics System Audio REQUIRED)

add_executable(
    app 
    src/main.cpp
    src/Game/Game.cpp
    src/Game/GameHandler.cpp
    src/Game/GameRender.cpp
    src/Hud/Hud.cpp
    src/Camera/Camera.cpp
    src/Player/Player.cpp
    src/Player/PlayerMovement.cpp
    src/Player/PlayerUpdate.cpp
    src/Map/Map.cpp 
    src/CollisionHandler/CollisionHandler.cpp
    src/Game/Coin.cpp
    src/Animation/Animation.cpp
)

target_link_libraries(app PRIVATE SFML::Window SFML::Graphics SFML::System SFML::Audio)