//
// Created by Brandon Martin on 4/1/19.
//

#include <cassert>
#include "Cursen/Drawing/CursesManager.h"
#include "AlarmManager.h"
#include "AlarmHandle.h"
#include "EventManager.h"

namespace cursen {

    AlarmManager *AlarmManager::instance = nullptr;
    unsigned int AlarmManager::ID = 0;

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
                privStopAlarm(entry->getId());
                Event event;
                event.type = EventType::AlarmExpire;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }

        }
        lastUpdate = std::chrono::system_clock::now();

    }

    void AlarmManager::privStopAlarm(unsigned int id) {
        stopRequests.push(id);
    }

    void AlarmManager::handleStartRequests() {
        Alarm *alarmEntry;
        while (!startRequests.empty()) {
            alarmEntry = startRequests.front();

            AlarmMap::iterator it = alarms.find(alarmEntry->getId());
            if (it == alarms.end()) {
                alarms[alarmEntry->getId()] = alarmEntry;
            }

            startRequests.pop();
        }
    }

    void AlarmManager::handleStopRequests() {
        unsigned int id;
        std::unordered_map<unsigned int, Alarm *>::iterator it;
        while (!stopRequests.empty()) {
            id = stopRequests.front();

            it = alarms.find(id);
            if (it != alarms.end()) {
                Alarm *entry = it->second;
                delete entry;
                alarms.erase(id);
            }

            stopRequests.pop();
        }
    }

    bool AlarmManager::privHasActiveAlarm(unsigned int id) {
        auto it = alarms.find(id);
        return it != alarms.end();
    }

    void AlarmManager::Terminate()
    {
        delete instance;
        instance = nullptr;
    }

    AlarmHandle AlarmManager::SetTimeout(AlarmManager::VoidFunc callback, double seconds)
    {
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = new Alarm(id, callback, seconds, Alarm::VOID, 0.0);
        alarm->reset();
        Instance().startRequests.push(alarm);

        return handle;
    }

    AlarmHandle AlarmManager::SetAlarm(VoidFunc callback, double seconds, double max_time, VoidFunc cancel_callback)
    {
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = new Alarm(id, callback, seconds, cancel_callback, max_time);
        alarm->reset();
        Instance().startRequests.push(alarm);

        return handle;
    }

    AlarmHandle AlarmManager::SetInterval(VoidFunc callback, double seconds)
    {
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = new Alarm(id, callback, seconds, Alarm::VOID, 0.0);
        alarm->reset();
        Instance().startRequests.push(alarm);

        return handle;
    }

    void AlarmManager::CancelAlarm(unsigned int id)
    {
        Instance().stopRequests.push(id);
    }

    void AlarmManager::ResetAlarm(unsigned int id)
    {
        auto& alarms = Instance().alarms;
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->reset();
    }

}