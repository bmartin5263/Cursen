//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMMANAGER_H
#define CURSEN_ALARMMANAGER_H

#include <functional>
#include <unordered_map>
#include <queue>
#include <chrono>
#include "AlarmEntry.h"

class Component;

class AlarmManager {

public:

    static void ProcessAlarms() { Instance().privProcessAlarms(); }
    static void StartTimer(Component* component, std::function<void()> f, double seconds) { Instance().privStartTimer(component, f, seconds); };
    static void StopTimer(Component* component) { Instance().privStopTimer(component); };

private:

    void privStartTimer(Component* component, std::function<void()> f, double seconds);
    void privStopTimer(Component* component);
    void privProcessAlarms();

    void handleStopRequests();
    void handleStartRequests();

    std::queue<AlarmEntry*> startRequests;
    std::queue<Component*> stopRequests;
    std::unordered_map<Component*, AlarmEntry*> alarms;
    std::chrono::system_clock::time_point lastUpdate;

    static AlarmManager* instance;

    static AlarmManager& Instance() {
        if (instance == nullptr)
            instance = new AlarmManager;
        return *instance;
    }

    AlarmManager();
    AlarmManager(const AlarmManager& other) = delete;
    AlarmManager(AlarmManager&& other) noexcept = delete;
    AlarmManager& operator = (const AlarmManager& other) = delete;
    AlarmManager& operator = (AlarmManager&& other) = delete;
    ~AlarmManager() = default;

};


#endif //CURSEN_ALARMMANAGER_H
