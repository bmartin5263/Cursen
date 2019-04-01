//
// Created by Brandon Martin on 4/1/19.
//

#include "AlarmEntry.h"

AlarmEntry::AlarmEntry(Component *component, std::function<void()> alarmFunction, double interval) :
    component(component), alarmFunction(alarmFunction), interval(interval), remaining(0.0)
{

}

void AlarmEntry::callAlarm() {
    alarmFunction();
}

bool AlarmEntry::updateTime(double elapsed) {
    remaining -= elapsed;
    if (remaining <= 0.0f) {
        remaining = interval;
        return true;
    }
    return false;
}

Component* AlarmEntry::getComponent() {
    return component;
}