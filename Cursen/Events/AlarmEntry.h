//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMENTRY_H
#define CURSEN_ALARMENTRY_H

#include <functional>

class Component;

class AlarmEntry {

public:

    AlarmEntry(Component* component, std::function<void()> alarmFunction, double interval);

    bool updateTime(double elapsed);
    void callAlarm();

    Component* getComponent();

private:

    Component* component;
    std::function<void()> alarmFunction;
    double interval;
    double remaining;

};


#endif //CURSEN_ALARMENTRY_H
