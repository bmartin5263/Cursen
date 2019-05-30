//
// Created by Brandon Martin on 4/1/19.
//

#ifndef CURSEN_ALARMENTRY_H
#define CURSEN_ALARMENTRY_H

#include <functional>

namespace cursen {

    class Component;

    class Alarm {

    public:

        typedef std::function<void()> VoidFun;

        static void VOID() {};

        Alarm(unsigned int id, VoidFun callback, double interval, VoidFun cancel_callback, double max_time);

        ~Alarm();

        void updateTime(double elapsed);

        bool ready();
        bool expired();

        void reset();
        void callInterval();
        void callExpire();

        unsigned int getId();

    private:

        unsigned int id;
        VoidFun interval_function;
        VoidFun cancel_function;
        double interval;
        double remaining;
        double total_time;
        bool has_total;

    };

}


#endif //CURSEN_ALARMENTRY_H
