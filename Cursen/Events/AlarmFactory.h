//
// Created by Brandon Martin on 5/30/19.
//

#ifndef CURSEN_ALARMFACTORY_H
#define CURSEN_ALARMFACTORY_H

#include <stack>
#include <functional>

namespace cursen {

    class Alarm;
    class AlarmFactory
    {

    public:

        typedef std::function<void()> VoidFun;

        static Alarm* CreateAlarm(unsigned int id, VoidFun callback, double interval, VoidFun cancel_callback, double max_time);
        static void RecycleAlarm(Alarm* alarm);

    private:

        std::stack<Alarm*> recycledItems;

        AlarmFactory() = default;
        AlarmFactory(const AlarmFactory&) = delete;
        AlarmFactory& operator = (const AlarmFactory&) = delete;
        ~AlarmFactory();

        static AlarmFactory& Instance()
        {
            static AlarmFactory instance;
            return instance;
        }
    };

}


#endif //CURSEN_ALARMFACTORY_H
