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
     * @brief Iterate through the alarms and call their interval functions if ready
     */
    static void ProcessAlarms() { Instance().privProcessAlarms(); }

    /**
     * @brief Create a new Alarm for a specified component
     *
     * @param component Component to register
     * @param interval_function Callback for each interval
     * @param seconds Seconds between each callback
     */
    static void StartAlarm(Component *component, VoidFunc interval_function, double seconds)
    {
        Instance().privStartAlarm(component, interval_function, seconds);
    };

    /**
     * @brief Stops and removes an Alarm from the update list
     *
     * @param component Component to deregister
     */
    static void StopAlarm(Component *component) { Instance().privStopAlarm(component); };

    /**
     * @brief Create a new Alarm that will automatically cancel itself after a specified time
     *
     * @param component Component to register
     * @param interval_function Callback for each interval
     * @param seconds Seconds between each callback
     * @param total_time Seconds before Alarm cancels itself
     * @param cancel_function Optional callback for when the Alarm is cancelled
     */
    static void StartAutoAlarm(Component *component, VoidFunc interval_function, double seconds, double total_time,
                               VoidFunc cancel_function = Alarm::VOID)
    {
        Instance().privStartAutoAlarm(component, interval_function, seconds, total_time, cancel_function);
    }

private:

    typedef std::queue<Alarm*> AlarmQueue;
    typedef std::queue<Component*> ComponentQueue;
    typedef std::unordered_map<Component*, Alarm*> AlarmMap;

    void privStartAlarm(Component *component, VoidFunc f, double seconds);
    void privStartAutoAlarm(Component *component, VoidFunc f, double seconds, double total_time, VoidFunc cf);
    void privStopAlarm(Component *component);
    void privProcessAlarms();

    void handleStopRequests();
    void handleStartRequests();

    AlarmQueue startRequests;       /// Queue for Component's requests to start Alarms
    ComponentQueue stopRequests;    /// Queue for Component's requests to cancel Alarms
    AlarmMap alarms;                /// Map Component* -> Alarm*
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
