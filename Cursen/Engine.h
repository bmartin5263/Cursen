//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_ENGINE_H
#define CURSEN_ENGINE_H

class Engine {

public:

    static void Run();
    static void Terminate();

private:

    void userInitialization();

    static Engine* engineInstance;

    static Engine& Instance() {
        if (engineInstance == nullptr)
            engineInstance = new Engine;
        return *engineInstance;
    }

    Engine() = default;
    Engine(const Engine& other) = delete;
    Engine(Engine&& other) noexcept = delete;
    Engine& operator = (const Engine& other) = delete;
    Engine& operator = (Engine&& other) = delete;
    ~Engine();

};

#endif //CURSEN_ENGINE_H
