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

    typedef std::function<void()> VoidFunc;

    static void ProcessAlarms() { Instance().privProcessAlarms(); }
    static void StartTimer(Component* component, VoidFunc interval_function, double seconds)
    {
        Instance().privStartTimer(component, interval_function, seconds);
    };

    static void StopTimer(Component* component) { Instance().privStopTimer(component); };
    static void StartAutoTimer(Component* component, VoidFunc interval_function, double seconds, double total_time, VoidFunc cancel_function = AlarmEntry::VOID)
    {
        Instance().privStartAutoTimer(component, interval_function, seconds, total_time, cancel_function);
    }

private:

    void privStartTimer(Component* component, VoidFunc f, double seconds);
    void privStartAutoTimer(Component* component, VoidFunc f, double seconds, double total_time, VoidFunc cf);
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
