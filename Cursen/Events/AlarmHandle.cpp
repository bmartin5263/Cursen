//
// Created by Brandon Martin on 5/29/19.
//

#include "AlarmHandle.h"
#include "AlarmManager.h"

namespace cursen {

    AlarmHandle::AlarmHandle() :
        id(0)
    {

    }

    AlarmHandle::AlarmHandle(unsigned int id) :
        id(id)
    {

    }

    void AlarmHandle::cancel()
    {
        if (id != 0) AlarmManager::CancelAlarm(id);
    }

    void AlarmHandle::getId(unsigned int& id)
    {
        id = this->id;
    }

    void AlarmHandle::reset()
    {
        if (id != 0) AlarmManager::ResetAlarm(id);
    }


}