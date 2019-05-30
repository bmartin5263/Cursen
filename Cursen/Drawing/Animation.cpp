//
// Created by Brandon Martin on 5/21/19.
//

#include "Animation.h"
#include "Frame.h"
#include "Cursen/Events/AlarmManager.h"

namespace cursen
{

    Animation::Animation() :
            currentFrame(0), numFrames(0), running(false)
    {

    }

    Frame& Animation::operator[](size_t i)
    {
        return frames[i];
    }

    Frame& Animation::addFrame(VoidFunction fn)
    {
        frames.push_back(Frame(fn));
        numFrames++;
        return frames.at(numFrames - 1);
    }

    Frame& Animation::addFrame(Frame frame)
    {
        frames.push_back(frame);
        numFrames++;
        return frames.at(numFrames - 1);
    }

    void Animation::removeFrame(size_t frame)
    {
        if (frame < frames.size())
        {
            frames.erase(frames.begin() + frame);
        }
    }

    bool Animation::getFrame(size_t i, Frame& frame)
    {
        if (i < frames.size())
        {
            frame = frames.at(i);
            return true;
        }
        return false;
    }

    void Animation::start()
    {
        currentFrame = 0;
        animationHandle = AlarmManager::SetInterval(std::bind(&Animation::nextFrame, this), speed);
        running = true;
    }

    void Animation::stop()
    {
        animationHandle.cancel();
        running = false;
    }

    void Animation::nextFrame()
    {
        frames[currentFrame]();
        currentFrame = (currentFrame + 1) % numFrames;
    }

    void Animation::initialize()
    {
        // TODO AlarmManager should not need components to operate
    }

    void Animation::setSpeed(double time)
    {
        this->speed = time;
    }

    double Animation::getSpeed()
    {
        return this->speed;
    }

    bool Animation::isRunning()
    {
        return this->running;
    }

}

