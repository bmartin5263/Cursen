//
// Created by Brandon Martin on 4/1/19.
//

#include "Cursen/Drawing/CursesManager.h"
#include "Alarm.h"

namespace cursen {

    Alarm::Alarm(unsigned int id, Alarm::VoidFun callback, double interval, Alarm::VoidFun cancel_callback,
                 double max_time) :
        id(id), interval_function(callback), cancel_function(cancel_callback), interval(interval), remaining(interval),
        total_time(max_time), has_total(total_time > 0.0), paused(false)
    {
    }

    void Alarm::initialize(unsigned int id, cursen::Alarm::VoidFun callback, double interval,
                           cursen::Alarm::VoidFun cancel_callback, double max_time)
    {
        this->id = id;
        this->interval_function = callback;
        this->interval = interval;
        this->cancel_function = cancel_callback;
        this->remaining = interval;
        this->total_time = max_time;
        this->has_total = total_time > 0.0;
        this->paused = false;
    }

    void Alarm::callInterval() {
        if (interval_function) interval_function();
    }

    void Alarm::callExpire() {
        if (cancel_function) cancel_function();
    }

    void Alarm::updateTime(double elapsed) {
        if (!paused) {
            remaining -= elapsed;
            total_time -= elapsed;
        }
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

    void Alarm::pause()
    {
        this->paused = true;
    }

    void Alarm::resume()
    {
        this->paused = false;
    }

    void Alarm::togglePaused()
    {
        this->paused = !this->paused;
    }
}
