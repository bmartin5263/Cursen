//
// Created by Brandon Martin on 4/1/19.
//

#include <cassert>
#include "Cursen/Drawing/TerminalManager.h"
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

    void AlarmManager::ProcessAlarms(AlarmManager::AlarmMap& alarmMap, AlarmQueue& startRequests, IntQueue& stopRequests)
    {
        auto& instance = Instance();
        auto event = Event{};
        instance.handleStopRequests(alarmMap, stopRequests);
        instance.handleStartRequests(alarmMap, startRequests);
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - instance.lastUpdate;
        for (auto it = alarmMap.begin(); it != alarmMap.end(); it++)
        {

            auto entry = it->second;
            entry->updateTime(elapsed_seconds.count());

            if (entry->ready())
            {
                entry->reset();
                event.type = EventType::AlarmInterval;
                event.alarm.alarmEntry = it->second;
                it->second->callInterval();
                //EventManager::PushEvent(event);
            }
            if (entry->expired())
            {
                stopRequests.push(entry->getId());
                event.type = EventType::AlarmExpire;
                event.alarm.alarmEntry = it->second;
                it->second->callExpire();
                //EventManager::PushEvent(event);
            }

        }
        instance.lastUpdate = std::chrono::system_clock::now();
    }

    void AlarmManager::handleStopRequests(AlarmManager::AlarmMap& alarmMap, IntQueue& stopRequests) const
    {
        while (!stopRequests.empty())
        {
            auto id = stopRequests.front();

            auto it = alarmMap.find(id);
            if (it != alarmMap.end())
            {
                Alarm* entry = it->second;
                AlarmFactory::RecycleAlarm(entry);
                alarmMap.erase(it);
            }

            stopRequests.pop();
        }
    }

    void AlarmManager::handleStartRequests(AlarmManager::AlarmMap& alarmMap, AlarmQueue& startRequests) const
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
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = AlarmFactory::CreateAlarm(id, callback, seconds, Alarm::VOID, seconds);
        alarm->reset();
        GetStartRequests().push(alarm);

        return handle;
    }

    AlarmHandle AlarmManager::SetInterval(VoidFunc callback, double seconds)
    {
        unsigned int id = ++ID;

        AlarmHandle handle(id);
        Alarm* alarm = AlarmFactory::CreateAlarm(id, callback, seconds, Alarm::VOID, 0.0);
        alarm->reset();
        GetStartRequests().push(alarm);

        return handle;
    }

    void AlarmManager::CancelAlarm(unsigned int id)
    {
        GetStopRequests().push(id);
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

    AlarmManager::IntQueue& AlarmManager::GetStopRequests()
    {
        return CursenApplication::GetCurrentForm()->getStopRequests();
    }

    AlarmManager::AlarmQueue& AlarmManager::GetStartRequests()
    {
        return CursenApplication::GetCurrentForm()->getStartRequests();
    }

}