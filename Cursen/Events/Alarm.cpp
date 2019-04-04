//
// Created by Brandon Martin on 4/1/19.
//

#include <Drawing/CursesManager.h>
#include "Alarm.h"

Alarm::Alarm(Component *component, std::function<void()> alarmFunction, double interval) :
    component(component), interval_function(alarmFunction), interval(interval), remaining(0.0), total_time(0.0),
    has_total(false)
{

}

Alarm::Alarm(Component *component, std::function<void()> alarmFunction, double interval,
                       double total_time, std::function<void()> cancel_function) :
        component(component), interval_function(alarmFunction), interval(interval), remaining(0.0), total_time(total_time),
        has_total(true), cancel_function(cancel_function)
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

Component* Alarm::getComponent() {
    return component;
}

Alarm::~Alarm() {
    //CursesManager::Flash();
}
