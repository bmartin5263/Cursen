//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_EVENT_H
#define CURSEN_EVENT_H

#include <cstdio>

#include "EventType.h"

namespace cursen {

    class Component;
    class Alarm;

    class Event {

    public:

        struct KeyEvent {
            int code;
        };

        struct ArrowEvent {
            ArrowEvent() {
                left = false;
                up = false;
                right = false;
                down = false;
            }

            bool left;
            bool up;
            bool right;
            bool down;
        };

        struct AlarmEvent {
            AlarmEvent() {
                alarmEntry = nullptr;
            }

            Alarm *alarmEntry;
        };

        Event() {
            key = KeyEvent();
            arrowPress = ArrowEvent();
            alarm = AlarmEvent();
        }

        EventType type;
        union
        {
            KeyEvent key;
            ArrowEvent arrowPress;
            AlarmEvent alarm;
        };

    };

    struct EnumClassHash {
        template<typename T>
        std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);
        }
    };

}

#endif //CURSEN_EVENT_H
