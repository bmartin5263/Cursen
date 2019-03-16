//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_EVENT_H
#define CURSEN_EVENT_H

#include <cstdio>

class Event {

public:

    struct KeyEvent
    {
        int code;
    };

    struct ArrowEvent
    {
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

    enum EventType
    {
        KeyPressed = 1,
        EscPressed = 2,
        DeletePressed = 4,
        EnterPressed = 8,
        ArrowPressed = 16,
        SocketConnected = 32,
        SocketDisconnected = 64,
        SocketMessage = 128,
    };

    EventType type;

    union
    {
        KeyEvent key;
        ArrowEvent arrowPress;
    };

    Event() {
        key = KeyEvent();
        arrowPress = ArrowEvent();
    }

};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};


#endif //CURSEN_EVENT_H
