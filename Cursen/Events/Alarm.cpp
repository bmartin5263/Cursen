//
// Created by Brandon Martin on 4/1/19.
//

#include "Cursen/Drawing/CursesManager.h"
#include "Alarm.h"

namespace cursen {

    Alarm::Alarm(unsigned int id, Alarm::VoidFun callback, double interval, Alarm::VoidFun cancel_callback,
                 double max_time) :
        id(id), interval_function(callback), interval(interval), remaining(interval), cancel_function(cancel_callback),
        total_time(max_time), has_total(total_time > 0.0)
    {

    }

    void Alarm::callInterval() {
        if (interval_function) {
            interval_function();
        }
    }

    void Alarm::callExpire() {
        if (cancel_function) {
            cancel_function();
        }
    }

    void Alarm::updateTime(double elapsed) {
        remaining -= elapsed;
        total_time -= elapsed;
    }

    bool Alarm::ready() {
        return remaining <= 0.0f;
    }

    bool Alarm::expired() {
        return has_total && (total_time <= 0.0f);
    }

    void Alarm::reset() {
        remaining = interval;
    }

    unsigned int Alarm::getId() {
        return id;
    }

    Alarm::~Alarm() {
        //CursesManager::Flash();
    }
}
