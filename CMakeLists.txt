cmake_minimum_required(VERSION 3.10)
project(TuProyecto)

set(CMAKE_CXX_STANDARD 17)

# Incluir directorios
include_directories(${CMAKE_SOURCE_DIR})

# Añadir todos los archivos fuente
set(SOURCES
    Bullet.cpp
    ButtonMenu.cpp
    Game.cpp
    Gamestates.cpp
    Tanque.cpp
    Temporizador.cpp
    Tutorial\ SFML.cpp
)

# Añadir SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(TuProyecto ${SOURCES})
target_link_libraries(TuProyecto sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

