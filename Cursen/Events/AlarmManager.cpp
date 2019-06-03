//
// Created by Brandon Martin on 4/1/19.
//

#include <cassert>
#include "Cursen/Drawing/CursesManager.h"
#include "AlarmManager.h"
#include "AlarmHandle.h"
#include "EventManager.h"
#include "AlarmFactory.h"

namespace cursen
{

    unsigned int AlarmManager::ID = 0;

    AlarmManager::AlarmManager()
    {
        AlarmFactory::Initialize();
        lastUpdate = std::chrono::system_clock::now();
    }


    void AlarmManager::privProcessAlarms()
    {

        Event event;
        handleStopRequests();
        handleStartRequests();
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - lastUpdate;
        for (auto it = alarms.begin(); it != alarms.end(); it++)
        {

            Alarm* entry = it->second;
            entry->updateTime(elapsed_seconds.count());

            if (entry->ready())
            {
                entry->reset();
                event.type = EventType::AlarmInterval;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }
            if (entry->expired())
            {
                stopRequests.push(entry->getId());
                event.type = EventType::AlarmExpire;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }

        }
        lastUpdate = std::chrono::system_clock::now();

    }

    void AlarmManager::handleStartRequests()
    {
        Alarm* alarmEntry;
        while (!startRequests.empty())
        {
            alarmEntry = startRequests.front();

            AlarmMap::iterator it = alarms.find(alarmEntry->getId());
            if (it == alarms.end())
            {
                alarms[alarmEntry->getId()] = alarmEntry;
            }

            startRequests.pop();
        }
    }

    void AlarmManager::handleStopRequests()
    {
        unsigned int id;
        std::unordered_map<unsigned int, Alarm*>::iterator it;
        while (!stopRequests.empty())
        {
            id = stopRequests.front();

            it = alarms.find(id);
            if (it != alarms.end())
            {
                Alarm* entry = it->second;
                AlarmFactory::RecycleAlarm(entry);
                alarms.erase(id);
            }

            stopRequests.pop();
        }
    }

    AlarmHandle AlarmManager::SetTimeout(AlarmManager::VoidFunc callback, double seconds)
    {
        AlarmManager& instance = Instance();
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = AlarmFactory::CreateAlarm(id, callback, seconds, Alarm::VOID, seconds);
        alarm->reset();
        instance.startRequests.push(alarm);

        return handle;
    }

    AlarmHandle AlarmManager::SetAlarm(VoidFunc callback, double seconds, double max_time, VoidFunc cancel_callback)
    {
        AlarmManager& instance = Instance();
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = AlarmFactory::CreateAlarm(id, callback, seconds, cancel_callback, max_time);
        alarm->reset();
        instance.startRequests.push(alarm);

        return handle;
    }

    AlarmHandle AlarmManager::SetInterval(VoidFunc callback, double seconds)
    {
        AlarmManager& instance = Instance();
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = AlarmFactory::CreateAlarm(id, callback, seconds, Alarm::VOID, 0.0);
        alarm->reset();
        instance.startRequests.push(alarm);

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

    void AlarmManager::PauseAlarm(unsigned int id)
    {
        auto& alarms = Instance().alarms;
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->pause();
    }

    void AlarmManager::ResumeAlarm(unsigned int id)
    {
        auto& alarms = Instance().alarms;
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->resume();
    }

    void AlarmManager::ToggleAlarm(unsigned int id)
    {
        auto& alarms = Instance().alarms;
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->togglePaused();
    }

    unsigned int AlarmManager::nextId()
    {
        // TODO Need to be edge condition safe (what if we reach the max number of id's?
        return ++ID;
    }

//    AlarmManager::AlarmMap::iterator AlarmManager::findAlarm(unsigned int id)
//    {
//        AlarmMap::iterator it;
//        auto& alarms = Instance().alarms;
//        auto found = alarms.find(id);
//        assert(found != alarms.end());
//        return alarms.find(id);
//    }

}