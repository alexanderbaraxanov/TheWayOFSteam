cmake_minimum_required(VERSION 3.8)
project(sfml-test)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

add_executable(app main.cpp)
target_link_libraries(app ${SFML_LIBRARIES})