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

    public:

        typedef std::function<void()> VoidFunc;

        static void Terminate();

        /**
         * @brief Iterate through the alarms and call their interval functions if ready
         */
        static void ProcessAlarms() { Instance().privProcessAlarms(); }

        /**
         * @brief Create a new Alarm for a specified component
         *
         * The Alarm is not immediately created but rather the request is added to a queue.
         * This is to make sure that the Alarm update list is not altered by one of its Alarms
         * during iteration. Before iteration, all requested Alarms are added.
         *
         * @param component Component to register
         * @param interval_function Callback for each interval
         * @param seconds Seconds between each callback
         * @param cancel_function Optional callback for when the Alarm is cancelled
         */
        //static void StartAlarm(Component *component, VoidFunc interval_function, double seconds,
        //                       VoidFunc cancel_function = Alarm::VOID)
        //{
        //    Instance().privStartAlarm(component, interval_function, seconds, cancel_function);
        //};

        /**
         * @brief Stops and removes an Alarm from the update list
         *
         * @param component Component to deregister
         */
        static void StopAlarm(unsigned int id) { Instance().privStopAlarm(id); };


        static void CancelAlarm(unsigned int id);

        /**
         * @brief Create a new Alarm that will automatically cancel itself after a specified time
         *
         * @param component Component to register
         * @param interval_function Callback for each interval
         * @param seconds Seconds between each callback
         * @param total_time Seconds before Alarm cancels itself
         * @param cancel_function Optional callback for when the Alarm is cancelled
         */
        //static void StartAutoAlarm(Component *component, VoidFunc interval_function, double seconds, double total_time,
        //                           VoidFunc cancel_function = Alarm::VOID)
        //{
        //    Instance().privStartAutoAlarm(component, interval_function, seconds, total_time, cancel_function);
        //}

        /**
         * @brief Check if Component has an Alarm in the update loop
         *
         * @param component Component to check
         * @return True if component has active alarm, false if otherwise
         */
        static bool HasActiveAlarm(unsigned int id) { return Instance().privHasActiveAlarm(id); }


        static AlarmHandle SetTimeout(VoidFunc callback, double seconds);
        static AlarmHandle SetAlarm(VoidFunc callback, double seconds, double max_time, VoidFunc cancel_callback);
        static AlarmHandle SetInterval(VoidFunc callback, double seconds);

        static void ResetAlarm(unsigned int id);

    private:

        static unsigned int ID;

        typedef std::queue<Alarm*> AlarmQueue;
        typedef std::queue<unsigned int> IntQueue;
        typedef std::unordered_map<unsigned int, Alarm*> AlarmMap;

        //void privStartAlarm(Component *component, VoidFunc interval_function, double seconds, VoidFunc cf);
        //void privStartAutoAlarm(Component *component, VoidFunc interval_function, double seconds, double total_time, VoidFunc cf);
        void privStopAlarm(unsigned int id);
        void privProcessAlarms();
        bool privHasActiveAlarm(unsigned int id);

        void handleStopRequests();
        void handleStartRequests();

        AlarmQueue startRequests;       /// Queue for Component's requests to start Alarms
        IntQueue stopRequests;    /// Queue for Component's requests to cancel Alarms
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


}

#endif //CURSEN_ALARMMANAGER_H
