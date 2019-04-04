//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMENTRY_H
#define CURSEN_ALARMENTRY_H

#include <functional>

class Component;

class Alarm {

public:

    typedef std::function<void()> VoidFun;

    static void VOID() {};

    Alarm(Component* component, VoidFun alarmFunction, double interval, VoidFun cancel_function);
    Alarm(Component* component, VoidFun alarmFunction, double interval,  VoidFun cancel_function, double total_time);

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
    VoidFun interval_function;
    VoidFun cancel_function;
    double interval;
    double remaining;
    double total_time;
    bool has_total;

};


#endif //CURSEN_ALARMENTRY_H
