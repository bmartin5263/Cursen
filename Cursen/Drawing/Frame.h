//
// Created by Brandon Martin on 5/21/19.
//

#ifndef CURSEN_FRAME_H
#define CURSEN_FRAME_H

#include <functional>

namespace cursen {

    class Frame
    {

    public:

        typedef std::function<void()> VoidFunction;

        Frame();
        Frame(VoidFunction& frame_function);

        void operator ()();

        void setFrameFunction(VoidFunction& frame_function);

        void setDuration(double time);
        double getDuration();

    private:

        double duration;
        VoidFunction frame_fn;

    };

}

#endif //CURSEN_FRAME_H
