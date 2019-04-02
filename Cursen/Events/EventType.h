//
// Created by Brandon Martin on 3/16/19.
//

#ifndef CURSEN_EVENTTYPE_H
#define CURSEN_EVENTTYPE_H

enum class EventType
{
    KeyPressed = 1,
    EscPressed = 2,
    DeletePressed = 4,
    EnterPressed = 8,
    ArrowPressed = 16,
    SocketConnected = 32,
    SocketDisconnected = 64,
    SocketMessage = 128,
    AlarmInterval = 256,
    AlarmExpire = 512,
};

#endif //CURSEN_EVENTTYPE_H
