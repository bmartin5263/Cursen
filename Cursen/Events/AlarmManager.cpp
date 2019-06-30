//
// Created by Brandon Martin on 4/1/19.
//

#include <cassert>
#include "Cursen/Drawing/CursesManager.h"
#include "AlarmManager.h"
#include "AlarmHandle.h"
#include "EventManager.h"
#include "AlarmFactory.h"
#include "Cursen/CursenApplication.h"

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
        assert(false);
        Event event;
        handleStopRequests();
        handleStartRequests();
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - lastUpdate;
        for (auto it = internal_alarms.begin(); it != internal_alarms.end(); it++)
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

    void AlarmManager::ProcessAlarms(AlarmManager::AlarmMap& alarmMap)
    {
        AlarmManager& instance = Instance();
        Event event;
        instance.handleStopRequests(alarmMap);
        instance.handleStartRequests(alarmMap);
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - instance.lastUpdate;
        for (auto it = alarmMap.begin(); it != alarmMap.end(); it++)
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
                instance.stopRequests.push(entry->getId());
                event.type = EventType::AlarmExpire;
                event.alarm.alarmEntry = it->second;
                EventManager::PushEvent(event);
            }

        }
        instance.lastUpdate = std::chrono::system_clock::now();
    }

    void AlarmManager::handleStartRequests()
    {
        assert(false);
        Alarm* alarmEntry;
        while (!startRequests.empty())
        {
            alarmEntry = startRequests.front();

            AlarmMap::iterator it = internal_alarms.find(alarmEntry->getId());
            if (it == internal_alarms.end())
            {
                internal_alarms[alarmEntry->getId()] = alarmEntry;
            }

            startRequests.pop();
        }
    }

    void AlarmManager::handleStopRequests()
    {
        assert(false);
        unsigned int id;
        std::unordered_map<unsigned int, Alarm*>::iterator it;
        while (!stopRequests.empty())
        {
            id = stopRequests.front();

            it = internal_alarms.find(id);
            if (it != internal_alarms.end())
            {
                Alarm* entry = it->second;
                AlarmFactory::RecycleAlarm(entry);
                internal_alarms.erase(id);
            }

            stopRequests.pop();
        }
    }

    void AlarmManager::handleStopRequests(AlarmManager::AlarmMap& alarmMap)
    {
        unsigned int id;
        std::unordered_map<unsigned int, Alarm*>::iterator it;
        while (!stopRequests.empty())
        {
            id = stopRequests.front();

            it = alarmMap.find(id);
            if (it != alarmMap.end())
            {
                Alarm* entry = it->second;
                AlarmFactory::RecycleAlarm(entry);
                alarmMap.erase(id);
            }

            stopRequests.pop();
        }
    }

    void AlarmManager::handleStartRequests(AlarmManager::AlarmMap& alarmMap)
    {
        Alarm* alarmEntry;
        while (!startRequests.empty())
        {
            alarmEntry = startRequests.front();

            AlarmMap::iterator it = alarmMap.find(alarmEntry->getId());
            if (it == alarmMap.end())
            {
                alarmMap[alarmEntry->getId()] = alarmEntry;
            }

            startRequests.pop();
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
        auto& alarms = GetAlarms();
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->reset();
    }

    void AlarmManager::PauseAlarm(unsigned int id)
    {
        auto& alarms = GetAlarms();
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->pause();
    }

    void AlarmManager::ResumeAlarm(unsigned int id)
    {
        auto& alarms = GetAlarms();
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->resume();
    }

    void AlarmManager::ToggleAlarm(unsigned int id)
    {
        auto& alarms = GetAlarms();
        auto found = alarms.find(id);
        assert(found != alarms.end());
        found->second->togglePaused();
    }

    unsigned int AlarmManager::nextId()
    {
        // TODO Need to be edge condition safe (what if we reach the max number of ids
        return ++ID;
    }

    AlarmManager& AlarmManager::Instance()
    {
        return CursenApplication::GetAlarmManager();
    }

    AlarmManager::~AlarmManager()
    {
        //for (auto& alarm : internal_alarms)
        //{
        //    AlarmFactory::RecycleAlarm(alarm.second);
        //}
    }

    std::unordered_map<unsigned int, Alarm*>& AlarmManager::GetAlarms()
    {
        return CursenApplication::GetCurrentForm()->getAlarmMap();
    }

}