//
// Created by Brandon Martin on 3/16/19.
//

#ifndef CURSEN_EVENTTYPE_H
#define CURSEN_EVENTTYPE_H

namespace cursen {

    enum class EventType
    {
        KeyPressed = 1,
        EscPressed = 2,
        DeletePressed = 4,
        EnterPressed = 8,
        ArrowPressed = 16,
        AlarmInterval = 32,
        AlarmExpire = 64,
        Update = 128,
        Null = 256
    };

}

#endif //CURSEN_EVENTTYPE_H
