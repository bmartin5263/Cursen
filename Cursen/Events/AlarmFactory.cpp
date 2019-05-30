//
// Created by Brandon Martin on 5/30/19.
//

#include "AlarmFactory.h"
#include "Alarm.h"

namespace cursen {

    Alarm* AlarmFactory::CreateAlarm(unsigned int id, VoidFun callback, double interval, VoidFun cancel_callback, double max_time)
    {
        AlarmFactory& instance = Instance();
        Alarm* alarm;

        if (instance.recycledItems.empty())
        {
            alarm = new Alarm();
        }
        else
        {
            alarm = instance.recycledItems.top();
            instance.recycledItems.pop();
        }

        alarm->initialize(id, callback, interval, cancel_callback, max_time);
        return alarm;
    }

    void AlarmFactory::RecycleAlarm(cursen::Alarm* alarm)
    {
        Instance().recycledItems.push(alarm);
    }

    AlarmFactory::~AlarmFactory()
    {
        while (!recycledItems.empty())
        {
            delete recycledItems.top();
            recycledItems.pop();
        }
    }

}