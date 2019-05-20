//
// Created by Brandon Martin on 5/19/19.
//

#ifndef CURSEN_INPUTMANAGER_H
#define CURSEN_INPUTMANAGER_H

namespace cursen {


    class InputManager {

    public:

        static void ProcessInput() { Instance().privProcessInput(); };

    private:

        void privProcessInput();

        static InputManager* instance;

        static InputManager& Instance() {
            if (instance == nullptr)
                instance = new InputManager;
            return *instance;
        }

        InputManager() = default;
        InputManager(const InputManager& other) = delete;
        InputManager(InputManager&& other) noexcept = delete;
        InputManager& operator = (const InputManager& other) = delete;
        InputManager& operator = (InputManager&& other) = delete;
        ~InputManager() = default;

    };

}

#endif //CURSEN_INPUTMANAGER_H
