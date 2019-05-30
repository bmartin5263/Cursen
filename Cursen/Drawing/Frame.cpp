//
// Created by Brandon Martin on 5/21/19.
//

#include "Frame.h"

namespace cursen {

    Frame::Frame() :
            duration(0.0)
    {
    }

    Frame::Frame(VoidFunction& frame_function) :
            frame_fn(frame_function), duration(0.0)
    {
    }

    void Frame::setFrameFunction(VoidFunction& frame_function)
    {
        this->frame_fn = frame_function;
    }

    void Frame::operator()()
    {
        if (frame_fn) {
            frame_fn();
        }
    }

    void Frame::setDuration(double time)
    {
        this->duration = time;
    }

    double Frame::getDuration()
    {
        return this->duration;
    }


}