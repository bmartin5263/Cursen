//
// Created by Brandon Martin on 5/19/19.
//

#include "InputManager.h"
#include "EventManager.h"
#include "Cursen/CursenApplication.h"
#include "Cursen/Drawing/CursesManager.h"

namespace cursen {

    void InputManager::privProcessInput() {
        auto key = getch();
        while (key != ERR) {

            if (key == '@') {
                auto& debugger = CursenApplication::GetDebugger();
                if (debugger.getInspectionPointer() != nullptr) {
                    debugger.deactivateInspection();
                } else {
                    debugger.activateInspection();
                }
                auto event = Event{};
                event.type = EventType::Null;
                EventManager::PushEvent(event);
            } else {
                auto event = Event{};
                if (key == CursesManager::ESCAPE) {
                    event.type = EventType::EscPressed;
                    event.key.code = key;
                } else if (key == CursesManager::BACKSPACE) {
                    event.type = EventType::DeletePressed;
                    event.key.code = key;
                } else if (key == CursesManager::ENTER) {
                    event.type = EventType::EnterPressed;
                    event.key.code = key;
                } else if (key == CursesManager::UP) {
                    event.type = EventType::ArrowPressed;
                    event.arrowPress.up = true;
                } else if (key == CursesManager::DOWN) {
                    event.type = EventType::ArrowPressed;
                    event.arrowPress.down = true;
                } else if (key == CursesManager::LEFT) {
                    event.type = EventType::ArrowPressed;
                    event.arrowPress.left = true;

                } else if (key == CursesManager::RIGHT) {
                    event.type = EventType::ArrowPressed;
                    event.arrowPress.right = true;
                } else {
                    event.type = EventType::KeyPressed;
                    event.key.code = key;
                }
                EventManager::PushEvent(event);
                Event any_key_press_event;
                any_key_press_event.type = EventType::AnyKeyPressed;
                any_key_press_event.key.code = key;
                EventManager::PushEvent(any_key_press_event);
            }
            key = getch();
        }
    }

    InputManager& InputManager::Instance()
    {
        return CursenApplication::GetInputManager();
    }

}