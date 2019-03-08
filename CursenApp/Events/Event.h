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

    enum EventType
    {
        KeyPressed = 1,
        EscPressed = 2,
        DeletePressed = 4,
        EnterPressed = 8,
        SocketConnected = 16,
        SocketDisconnected = 32,
        SocketMessage = 64,
    };

    EventType type;

    union
    {
        KeyEvent key;
    };

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
