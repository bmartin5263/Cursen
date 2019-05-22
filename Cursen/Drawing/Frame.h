//
// Created by Brandon Martin on 5/21/19.
//

#ifndef CURSEN_FRAME_H
#define CURSEN_FRAME_H

#include <functional>

namespace cursen {

    typedef std::function<void()> VoidFunction;

    class Frame
    {

    public:

        Frame();
        Frame(VoidFunction& frame_function);

        void operator ()();

        void setFrameFunction(VoidFunction& frame_function);

    private:

        VoidFunction frame_fn;

    };

}

#endif //CURSEN_FRAME_H
