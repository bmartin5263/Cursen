//
// Created by Brandon Martin on 4/1/19.
//

#include <Drawing/CursesManager.h>
#include "AlarmManager.h"
#include "EventManager.h"

AlarmManager* AlarmManager::instance = nullptr;

AlarmManager::AlarmManager() {
    lastUpdate = std::chrono::system_clock::now();
}


void AlarmManager::privProcessAlarms() {

    handleStartRequests();
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - lastUpdate;
    for (auto it = alarms.begin(); it != alarms.end(); it++) {

        if (it->second->updateTime(elapsed_seconds.count())) {
            Event event;
            event.type = EventType::Alarm;
            event.alarm.alarmEntry = it->second;
            EventManager::PushEvent(event);
        }

    }
    lastUpdate = std::chrono::system_clock::now();
    handleStopRequests();

}

void AlarmManager::privStartTimer(Component *component, std::function<void()> f, double interval) {
    startRequests.push(new AlarmEntry(component, f, interval));
}

void AlarmManager::privStopTimer(Component *component) {
    stopRequests.push(component);
}

void AlarmManager::handleStartRequests() {
    AlarmEntry* alarmEntry;
    std::unordered_map<Component*, AlarmEntry*>::iterator it;
    while (!startRequests.empty()) {
        alarmEntry = startRequests.front();

        it = alarms.find(alarmEntry->getComponent());
        if (it == alarms.end() )
        {
            alarms[alarmEntry->getComponent()] = alarmEntry;
        }

        startRequests.pop();
    }
}

void AlarmManager::handleStopRequests() {
    Component* component;
    std::unordered_map<Component*, AlarmEntry*>::iterator it;
    while (!stopRequests.empty()) {
        component = stopRequests.front();

        it = alarms.find(component);
        if (it != alarms.end() )
        {
            AlarmEntry* entry = it->second;
            delete entry;
            alarms.erase(component);
        }

        stopRequests.pop();
    }
}