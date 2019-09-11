//
// Created by Brandon Martin on 5/19/19.
//

#ifndef CURSEN_INPUTMANAGER_H
#define CURSEN_INPUTMANAGER_H

#include <unordered_set>
#include <chrono>

namespace cursen {

    class InputManager {

    public:

        static void ProcessInput() { Instance().privProcessInput(); };

    private:

        void privProcessInput();

        std::chrono::system_clock::time_point last_update;

        //std::unordered_set<int> keys_pressed;
        //std::unordered_set<int> keys_pressed_previous;

        friend class CursenApplication;
        static InputManager& Instance();

        InputManager();
        InputManager(const InputManager& other) = delete;
        InputManager(InputManager&& other) noexcept = delete;
        InputManager& operator = (const InputManager& other) = delete;
        InputManager& operator = (InputManager&& other) = delete;
        ~InputManager() = default;

    };

}

#endif //CURSEN_INPUTMANAGER_H
