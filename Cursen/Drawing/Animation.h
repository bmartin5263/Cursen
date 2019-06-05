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

    class Animation
    {

    public:

        /**
         * @brief Construct an empty animation.
         */
        Animation();

        /**
         * @brief Construct an empty animation with space reserved for the specified number of frames.
         *
         * @param num_frames Number of frames to reserve space for
         */
        explicit Animation(size_t num_frames);

        /**
         * @brief Get the frame at the specified position. Does not perform bounds checking.
         *
         * @param index
         * @return Frame at specified position.
         */
        Frame& operator[](size_t index);

        /* Frames */

        /**
         * @brief Add a frame to this animation.
         *
         * This method returns a reference to the added Frame so you can chain methods on the frame
         * for additional customization.
         *
         * @code myAnimation.add(frame).setDuration(2.0);
         *
         * @param frame Frame to add
         * @return Reference to added Frame
         */
        Frame& add(Frame frame);

        /**
         * @brief Add a frame to this animation constructed from a function.
         *
         * A frame will be implicitly constructed with the supplied callback.
         *
         * This method returns a reference to the added Frame so you can chain methods on the frame
         * for additional customization.
         *
         * @code myAnimation.add([&]() { myLabel.setText("Hello World!"; }).setDuration(2.0);
         *
         * @param fn Function to call for the new frame
         * @return Reference to added Frame
         */
        Frame& add(Frame::VoidFunction fn);

        /**
         * Get the frame by reference at the specified position. Performs bounds checking.
         *
         * @param i Index of Frame
         * @param frame Return value for Frame
         * @return Frame at specified position.
         */
        bool getFrame(size_t i, Frame& frame);

        /**
         * @brief Remove the frame at the specified position. Performs bounds checking.
         *
         * @param i Index of frame to remove.
         */
        void removeFrame(size_t i);

        /* Speed */

        /**
         * @brief Set the duration for each frame.
         *
         * Frames that have a specified duration greater than 0.0 seconds will override this
         * duration.
         *
         * @param time Seconds per frame
         */
        void setDuration(double time);

        /**
         * @brief Get the animation duration.
         *
         * @return Seconds per frame
         */
        double getDuration();
        
        // TODO: Keep this internal
        void setVariableTime(bool value);

        /* Animation Control */
        void start();
        void stop();
        void pause();
        void resume();

        bool isRunning();

        /* Animation Fn */

        /**
         * @brief Call the current Frame's callback and move to the next Frame
         *
         * This method can be used to step frame-by-frame through an animation manually,
         * but is used internally in conjunction with Time functions to play through the animation
         * automatically.
         */
        void nextFrame();

    private:

        AlarmHandle animationHandle;

        double default_duration;
        size_t currentFrame;
        size_t numFrames;
        std::vector<Frame> frames;
        bool running;
        bool paused;
        bool variable_time;

    };

}

#endif //CURSEN_ANIMATION_H
