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

    AlarmHandle& AlarmHandle::operator=(const AlarmHandle& other)
    {
        if (&other != this)
        {
            AlarmManager::CancelAlarm(id);
            this->id = other.id;
        }
        return *this;
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

    void AlarmHandle::pause()
    {
        if (id != 0) AlarmManager::PauseAlarm(id);
    }

    void AlarmHandle::resume()
    {
        if (id != 0) AlarmManager::ResumeAlarm(id);
    }

    void AlarmHandle::toggle()
    {
        if (id != 0) AlarmManager::ToggleAlarm(id);
    }



}