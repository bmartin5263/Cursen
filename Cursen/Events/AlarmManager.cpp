//
// Created by Brandon Martin on 4/1/19.
//

#include <Drawing/CursesManager.h>
#include "AlarmManager.h"
#include "EventManager.h"

namespace cursen {

    AlarmManager *AlarmManager::instance = nullptr;

    AlarmManager::AlarmManager() {
        lastUpdate = std::chrono::system_clock::now();
    }


    void AlarmManager::privProcessAlarms() {

        handleStopRequests();
        handleStartRequests();
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - lastUpdate;
        for (auto it = alarms.begin(); it != alarms.end(); it++) {

            Alarm *entry = it->second;
            entry->updateTime(elapsed_seconds.count());

            if (entry->ready()) {
                entry->reset();
                Event event;
                event.type = EventType::AlarmInterval;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }
            if (entry->expired()) {
                privStopAlarm(entry->getComponent());
                Event event;
                event.type = EventType::AlarmExpire;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }

        }
        lastUpdate = std::chrono::system_clock::now();

    }

    void AlarmManager::privStartAlarm(Component *component, VoidFunc interval_function, double seconds, VoidFunc cf) {
        startRequests.push(new Alarm(component, interval_function, seconds, cf));
    }

    void AlarmManager::privStartAutoAlarm(Component *component, VoidFunc interval_function, double seconds,
                                          double total_time, VoidFunc cf) {
        startRequests.push(new Alarm(component, interval_function, seconds, cf, total_time));
    }

    void AlarmManager::privStopAlarm(Component *component) {
        stopRequests.push(component);
    }

    void AlarmManager::handleStartRequests() {
        Alarm *alarmEntry;
        std::unordered_map<Component *, Alarm *>::iterator it;
        while (!startRequests.empty()) {
            alarmEntry = startRequests.front();

            it = alarms.find(alarmEntry->getComponent());
            if (it == alarms.end()) {
                alarms[alarmEntry->getComponent()] = alarmEntry;
            }

            startRequests.pop();
        }
    }

    void AlarmManager::handleStopRequests() {
        Component *component;
        std::unordered_map<Component *, Alarm *>::iterator it;
        while (!stopRequests.empty()) {
            component = stopRequests.front();

            it = alarms.find(component);
            if (it != alarms.end()) {
                Alarm *entry = it->second;
                delete entry;
                alarms.erase(component);
            }

            stopRequests.pop();
        }
    }

    bool AlarmManager::privHasActiveAlarm(Component *component) {
        auto it = alarms.find(component);
        return it != alarms.end();
    }

}