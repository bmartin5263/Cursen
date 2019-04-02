//
// Created by Brandon Martin on 4/1/19.
//

#include <Drawing/CursesManager.h>
#include "AlarmEntry.h"

AlarmEntry::AlarmEntry(Component *component, std::function<void()> alarmFunction, double interval) :
    component(component), interval_function(alarmFunction), interval(interval), remaining(0.0), total_time(0.0),
    has_total(false)
{

}

AlarmEntry::AlarmEntry(Component *component, std::function<void()> alarmFunction, double interval,
                       double total_time, std::function<void()> cancel_function) :
        component(component), interval_function(alarmFunction), interval(interval), remaining(0.0), total_time(total_time),
        has_total(true), cancel_function(cancel_function)
{

}

void AlarmEntry::callInterval() {
    interval_function();
}

void AlarmEntry::callExpire() {
    if (cancel_function) {
        cancel_function();
    }
}

void AlarmEntry::updateTime(double elapsed) {
    remaining -= elapsed;
    total_time -= elapsed;
}

bool AlarmEntry::ready() {
    return remaining <= 0.0f;
}

bool AlarmEntry::expired() {
    return has_total && (total_time <= 0.0f);
}

void AlarmEntry::reset() {
    remaining = interval;
}

Component* AlarmEntry::getComponent() {
    return component;
}

AlarmEntry::~AlarmEntry() {
    //CursesManager::Flash();
}
