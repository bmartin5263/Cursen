cmake_minimum_required(VERSION 3.10)
project(Cursen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lncurses -lpanel")

add_executable(Cursen main.cpp Cursen/Engine.cpp Cursen/Engine.h Cursen/TerminalManager.cpp Cursen/TerminalManager.h Cursen/UserInterface/Canvas.cpp Cursen/UserInterface/Canvas.h Cursen/UserInterface/CursesSprite.cpp Cursen/UserInterface/CursesSprite.h Cursen/UserInterface/UITools.cpp Cursen/UserInterface/UITools.h)

target_include_directories(Cursen PRIVATE Cursen)
target_include_directories(Cursen PRIVATE Cursen/UserInterface)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cursen ${SFML_LIBRARIES})
endif()