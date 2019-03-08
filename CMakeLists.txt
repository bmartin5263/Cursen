cmake_minimum_required(VERSION 3.10)
project(Cursen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-Wno-unused-command-line-argument -lncurses -lpanel")

add_executable(Cursen main.cpp Cursen/Engine.cpp Cursen/Engine.h Cursen/TerminalManager.cpp Cursen/TerminalManager.h Cursen/UI/Sprites/CursenSprite.cpp Cursen/UI/Sprites/CursenSprite.h Cursen/UI/UITools.cpp Cursen/UI/UITools.h Cursen/SceneManager.cpp Cursen/SceneManager.h Cursen/EngineClock.cpp Cursen/EngineClock.h "Cursen/User Classes/Scene.cpp" "Cursen/User Classes/Scene.h" "Cursen/User Classes/CursenObject.cpp" "Cursen/User Classes/CursenObject.h" Demo/BouncyBox.cpp Demo/BouncyBox.h Cursen/UI/Sprites/SpriteFrame.cpp Cursen/UI/Sprites/SpriteFrame.h Cursen/UI/Sprites/SpriteManager.cpp Cursen/UI/Sprites/SpriteManager.h Cursen/ResourceManager.cpp Cursen/ResourceManager.h Cursen/UI/Sprites/SpriteFileParser.cpp Cursen/UI/Sprites/SpriteFileParser.h Cursen/Debugging/DebugConsole.cpp Cursen/Debugging/DebugConsole.h Cursen/StopWatch.cpp Cursen/StopWatch.h CursenApp/CursenApplication.cpp CursenApp/CursenApplication.h CursenApp/Components/Form.cpp CursenApp/Components/Form.h CursenApp/Events/EventManager.cpp CursenApp/Events/EventManager.h CursenApp/Events/Event.cpp CursenApp/Events/Event.h CursenApp/CursesManager.cpp CursenApp/CursesManager.h CursenApp/Components/Component.cpp CursenApp/Components/Component.h CursenApp/Components/Cursor.cpp CursenApp/Components/Cursor.h)

target_include_directories(Cursen PRIVATE Cursen)
target_include_directories(Cursen PRIVATE CursenApp)
target_include_directories(Cursen PRIVATE Cursen/UI)
target_include_directories(Cursen PRIVATE Cursen/UI/Sprites)
target_include_directories(Cursen PRIVATE Cursen/Debugging)
target_include_directories(Cursen PRIVATE Cursen/User\ Classes)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cursen ${SFML_LIBRARIES})
endif()