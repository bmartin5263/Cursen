//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMENTRY_H
#define CURSEN_ALARMENTRY_H

#include <functional>

class Component;

class Alarm {

public:

    static void VOID() {};

    Alarm(Component* component, std::function<void()> alarmFunction, double interval);
    Alarm(Component* component, std::function<void()> alarmFunction, double interval, double total_time,  std::function<void()> cancel_function);

    ~Alarm();

    void updateTime(double elapsed);

    bool ready();
    bool expired();

    void reset();
    void callInterval();
    void callExpire();

    Component* getComponent();

private:

    Component* component;
    std::function<void()> interval_function;
    std::function<void()> cancel_function;
    double interval;
    double remaining;
    double total_time;
    bool has_total;

};


#endif //CURSEN_ALARMENTRY_H
