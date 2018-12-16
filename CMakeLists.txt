cmake_minimum_required(VERSION 3.10)
project(Cursen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-lncurses -lpanel")

add_executable(Cursen main.cpp Cursen/Engine.cpp Cursen/Engine.h Cursen/TerminalManager.cpp Cursen/TerminalManager.h Cursen/UserInterface/Sprites/CursenSprite.cpp Cursen/UserInterface/Sprites/CursenSprite.h Cursen/UserInterface/UITools.cpp Cursen/UserInterface/UITools.h Cursen/SceneManager.cpp Cursen/SceneManager.h Cursen/EngineClock.cpp Cursen/EngineClock.h "Cursen/User Classes/Scene.cpp" "Cursen/User Classes/Scene.h" "Cursen/User Classes/CursenObject.cpp" "Cursen/User Classes/CursenObject.h" Demo/BouncyBox.cpp Demo/BouncyBox.h Cursen/InputHelper.h Cursen/UserInterface/Sprites/SpriteFrame.cpp Cursen/UserInterface/Sprites/SpriteFrame.h)

target_include_directories(Cursen PRIVATE Cursen)
target_include_directories(Cursen PRIVATE Cursen/UserInterface)
target_include_directories(Cursen PRIVATE Cursen/User\ Classes)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cursen ${SFML_LIBRARIES})
endif()