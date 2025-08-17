cmake_minimum_required(VERSION 3.17)
project(SFML-platformer)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(SFML 3 REQUIRED COMPONENTS Window System Graphics)
add_executable(${PROJECT_NAME}
	SFML-platformer/main.cpp
	SFML-platformer/Game.cpp
	SFML-platformer/Platform.cpp
	SFML-platformer/Player.cpp)

target_precompile_headers(${PROJECT_NAME} PUBLIC SFML-platformer/stdafx.h)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Window SFML::System SFML::Graphics)
