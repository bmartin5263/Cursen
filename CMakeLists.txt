cmake_minimum_required(VERSION 3.10)
project(Cursen)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-Wno-unused-command-line-argument -lncurses -lpanel")

add_executable(Cursen main.cpp CursenOld/Engine.cpp CursenOld/Engine.h CursenOld/TerminalManager.cpp CursenOld/TerminalManager.h CursenOld/UI/Sprites/CursenSprite.cpp CursenOld/UI/Sprites/CursenSprite.h CursenOld/UI/UITools.cpp CursenOld/UI/UITools.h CursenOld/SceneManager.cpp CursenOld/SceneManager.h CursenOld/EngineClock.cpp CursenOld/EngineClock.h "CursenOld/User Classes/Scene.cpp" "CursenOld/User Classes/Scene.h" "CursenOld/User Classes/CursenObject.cpp" "CursenOld/User Classes/CursenObject.h" Demo/BouncyBox.cpp Demo/BouncyBox.h CursenOld/UI/Sprites/SpriteFrame.cpp CursenOld/UI/Sprites/SpriteFrame.h CursenOld/UI/Sprites/SpriteManager.cpp CursenOld/UI/Sprites/SpriteManager.h CursenOld/ResourceManager.cpp CursenOld/ResourceManager.h CursenOld/UI/Sprites/SpriteFileParser.cpp CursenOld/UI/Sprites/SpriteFileParser.h CursenOld/Debugging/DebugConsole.cpp CursenOld/Debugging/DebugConsole.h CursenOld/StopWatch.cpp CursenOld/StopWatch.h Cursen/CursenApplication.cpp Cursen/CursenApplication.h Cursen/Components/Form.cpp Cursen/Components/Form.h Cursen/Events/EventManager.cpp Cursen/Events/EventManager.h Cursen/Events/Event.cpp Cursen/Events/Event.h Cursen/Drawing/CursesManager.cpp Cursen/Drawing/CursesManager.h Cursen/Components/Component.cpp Cursen/Components/Component.h Cursen/Cursor/Cursor.cpp Cursen/Cursor/Cursor.h Cursen/Drawing/TextBody.cpp Cursen/Drawing/TextBody.h Cursen/Drawing/Vect2i.h Demo/TestForm.cpp Demo/TestForm.h Cursen/Components/Label.cpp Cursen/Components/Label.h Cursen/Cursor/ArrowMap.h Cursen/Drawing/Color.cpp Cursen/Drawing/Color.h Cursen/Drawing/TextAlignment.h Cursen/Cursor/ClickFlag.h Cursen/Events/EventType.h Cursen/Components/Box.cpp Cursen/Components/Box.h Cursen/Drawing/ColorPair.cpp Cursen/Drawing/ColorPair.h Cursen/Drawing/ColorPalette.cpp Cursen/Drawing/ColorPalette.h Cursen/Components/ColorComponent.cpp Cursen/Components/ColorComponent.h Cursen/Components/CheckBox.cpp Cursen/Components/CheckBox.h Cursen/Components/CheckState.h Cursen/Events/InputManager.cpp Cursen/Events/InputManager.h Cursen/Events/EventQueue.h Cursen/Events/EventQueue.cpp)

target_include_directories(Cursen PRIVATE CursenOld)
target_include_directories(Cursen PRIVATE Cursen)
target_include_directories(Cursen PRIVATE CursenOld/UI)
target_include_directories(Cursen PRIVATE CursenOld/UI/Sprites)
target_include_directories(Cursen PRIVATE CursenOld/Debugging)
target_include_directories(Cursen PRIVATE CursenOld/User\ Classes)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cursen ${SFML_LIBRARIES})
endif()