//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMMANAGER_H
#define CURSEN_ALARMMANAGER_H

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <chrono>

#include "Alarm.h"
#include "AlarmHandle.h"

namespace cursen {

    class Component;

    class AlarmManager {

    private:

        typedef std::function<void()> VoidFunc;
        typedef std::chrono::system_clock::time_point TimePoint;
        typedef std::unordered_map<unsigned int, Alarm*> AlarmMap;
        typedef std::queue<Alarm*> AlarmQueue;
        typedef std::queue<unsigned int> IntQueue;

    public:

        /**
         * @brief Iterate through the alarms and call their interval functions if ready
         */
        static void ProcessAlarms(AlarmMap& alarmMap, AlarmQueue& startRequests, IntQueue& stopRequests);

        /**
         * @brief Stops and removes an Alarm from the update list
         *
         * @param id Id of Alarm to cancel
         */
        static void CancelAlarm(unsigned int id);

        /**
         * @brief Pauses an alarm so its internal clock won't update with each cycle
         *
         * @param id Id of Alarm to pause
         */
        static void PauseAlarm(unsigned int id);

        /**
         * @brief Resume an alarm so its internal clock will update with each cycle
         *
         * @param id Id of Alarm to resume
         */
        static void ResumeAlarm(unsigned int id);

        /**
         * @brief Toggle an Alarm's status between paused and not paused
         *
         * @param id Id of Alarm to toggle
         */
        static void ToggleAlarm(unsigned int id);

        static void ResetAlarm(unsigned int id);

        static AlarmMap& GetAlarms();
        static IntQueue& GetStopRequests();
        static AlarmQueue& GetStartRequests();

        static AlarmHandle SetTimeout(VoidFunc callback, double seconds);
        static AlarmHandle SetInterval(VoidFunc callback, double seconds);

    private:

        static unsigned int ID;

        unsigned int nextId();
        void handleStopRequests(AlarmMap& alarmMap, IntQueue& stopRequests) const;
        void handleStartRequests(AlarmMap& alarmMap, AlarmQueue& startRequests) const;

        AlarmMap internal_alarms;       /// Map unsigned int -> Alarm*
        TimePoint lastUpdate;           /// TimePoint for the last time ProcessAlarms was called

        static AlarmManager& Instance();
        friend class CursenApplication;

        AlarmManager();
        AlarmManager(const AlarmManager& other) = delete;
        AlarmManager(AlarmManager&& other) noexcept = delete;
        AlarmManager& operator = (const AlarmManager& other) = delete;
        AlarmManager& operator = (AlarmManager&& other) = delete;
        ~AlarmManager();

    };


}

#endif //CURSEN_ALARMMANAGER_H
