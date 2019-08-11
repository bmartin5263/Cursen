//
// Created by Brandon Martin on 5/29/19.
//

#ifndef CURSEN_ALARMHANDLE_H
#define CURSEN_ALARMHANDLE_H

#include "Cursen/Handle/Handle.h"

namespace cursen {

    class AlarmHandle
    {

    public:

        AlarmHandle();
        AlarmHandle(unsigned int id);
        AlarmHandle& operator = (const AlarmHandle& other);
        ~AlarmHandle();


        void cancel();
        void reset();
        void pause();
        void resume();
        void toggle();

        void getId(unsigned int& id);

    private:

        unsigned int id;
        //HANDLE_VARIABLE

    };


}

#endif //CURSEN_ALARMHANDLE_H
