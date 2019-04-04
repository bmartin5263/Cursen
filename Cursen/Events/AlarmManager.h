//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMMANAGER_H
#define CURSEN_ALARMMANAGER_H

#include <functional>
#include <unordered_map>
#include <queue>
#include <chrono>
#include "Alarm.h"

class Component;

class AlarmManager {

public:

    typedef std::function<void()> VoidFunc;

    /**
     * \brief Iterate through the alarms and call their interval functions if ready
     */
    static void ProcessAlarms() { Instance().privProcessAlarms(); }

    /**
     * \brief Create a new alarm for a specified component
     */
    static void StartAlarm(Component *component, VoidFunc interval_function, double seconds)
    {
        Instance().privStartAlarm(component, interval_function, seconds);
    };

    static void StopAlarm(Component *component) { Instance().privStopAlarm(component); };
    static void StartAutoAlarm(Component *component, VoidFunc interval_function, double seconds, double total_time,
                               VoidFunc cancel_function = Alarm::VOID)
    {
        Instance().privStartAutoAlarm(component, interval_function, seconds, total_time, cancel_function);
    }

private:

    void privStartAlarm(Component *component, VoidFunc f, double seconds);
    void privStartAutoAlarm(Component *component, VoidFunc f, double seconds, double total_time, VoidFunc cf);
    void privStopAlarm(Component *component);
    void privProcessAlarms();

    void handleStopRequests();
    void handleStartRequests();

    std::queue<Alarm*> startRequests;
    std::queue<Component*> stopRequests;
    std::unordered_map<Component*, Alarm*> alarms;
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
