//
// Created by Brandon Martin on 5/21/19.
//

#ifndef CURSEN_ANIMATION_H
#define CURSEN_ANIMATION_H

#include <vector>

#include "Frame.h"
#include "Cursen/Components/Component.h"
#include "Cursen/Events/AlarmManager.h"

namespace cursen {

    class Animation : public Component
    {

    public:

        Animation();

        void initialize() override;

        Frame& operator[](size_t);

        /* Frames */
        Frame& addFrame(Frame frame);
        Frame& addFrame(VoidFunction fn);
        bool getFrame(size_t i, Frame& frame);
        void removeFrame(size_t frame);

        /* Speed */
        void setSpeed(double time);
        double getSpeed();

        /* Animation Control */
        void start();
        void stop();
        bool isRunning();

        /* Animation Fn */
        void nextFrame();

    private:

        AlarmHandle animationHandle;

        double speed;
        size_t currentFrame;
        size_t numFrames;
        std::vector<Frame> frames;
        bool running;

    };

}

#endif //CURSEN_ANIMATION_H
