//
// Created by Brandon Martin on 5/21/19.
//

#include "Frame.h"

namespace cursen {

    Frame::Frame()
    {

    }

    Frame::Frame(VoidFunction& frame_function) :
            frame_fn(frame_function)
    {
    }

    void Frame::setFrameFunction(cursen::VoidFunction& frame_function)
    {
        this->frame_fn = frame_function;
    }

    void Frame::operator()()
    {
        if (frame_fn) {
            frame_fn();
        }
    }


}