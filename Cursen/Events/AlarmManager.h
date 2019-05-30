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

    public:

        /**
         * @brief Iterate through the alarms and call their interval functions if ready
         */
        static void ProcessAlarms() { Instance().privProcessAlarms(); }

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

        static AlarmHandle SetTimeout(VoidFunc callback, double seconds);
        static AlarmHandle SetAlarm(VoidFunc callback, double seconds, double max_time, VoidFunc cancel_callback);
        static AlarmHandle SetInterval(VoidFunc callback, double seconds);

    private:

        static unsigned int ID;

        typedef std::queue<Alarm*> AlarmQueue;
        typedef std::queue<unsigned int> IntQueue;
        typedef std::unordered_map<unsigned int, Alarm*> AlarmMap;

        void privProcessAlarms();
        unsigned int nextId();
        void handleStopRequests();
        void handleStartRequests();

        AlarmQueue startRequests;       /// Queue for requests to start Alarms
        IntQueue stopRequests;          /// Queue for requests to cancel Alarms
        AlarmMap alarms;                /// Map unsigned int -> Alarm*
        TimePoint lastUpdate;           /// TimePoint for the last time ProcessAlarms was called

        static AlarmManager& Instance() {
            static AlarmManager instance;
            return instance;
        }

        AlarmManager();
        AlarmManager(const AlarmManager& other) = delete;
        AlarmManager(AlarmManager&& other) noexcept = delete;
        AlarmManager& operator = (const AlarmManager& other) = delete;
        AlarmManager& operator = (AlarmManager&& other) = delete;
        ~AlarmManager() = default;

    };


}

#endif //CURSEN_ALARMMANAGER_H
