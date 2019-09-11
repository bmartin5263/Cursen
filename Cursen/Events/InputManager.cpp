//
// Created by Brandon Martin on 5/19/19.
//

#include "InputManager.h"
#include "EventManager.h"
#include "Cursen/CursenApplication.h"
#include "Cursen/Drawing/CursesManager.h"

namespace cursen {

    InputManager::InputManager()
    {
        last_update = std::chrono::system_clock::now();
    }

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

//                if (keys_pressed.find(key) == keys_pressed.end())
//                {
//                    keys_pressed.insert(key);
//                }

            }
            key = getch();
        }
//        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_update).count() >= 199)
//        {
//            for (auto curr_key : keys_pressed)
//            {
//                if (keys_pressed_previous.find(curr_key) == keys_pressed_previous.end())
//                {
//                    Event key_down_event;
//                    key_down_event.type = EventType::KeyDown;
//                    key_down_event.key.code = curr_key;
//                    EventManager::PushEvent(key_down_event);
//                }
//            }
//            for (auto prev_key : keys_pressed_previous)
//            {
//                if (keys_pressed.find(prev_key) == keys_pressed.end())
//                {
//                    Event key_up_event;
//                    key_up_event.type = EventType::KeyUp;
//                    key_up_event.key.code = prev_key;
//                    EventManager::PushEvent(key_up_event);
//                }
//            }
//            keys_pressed_previous = keys_pressed;
//            keys_pressed.clear();
//            last_update = std::chrono::system_clock::now();
//        }
    }

    InputManager& InputManager::Instance()
    {
        return CursenApplication::GetInputManager();
    }

}