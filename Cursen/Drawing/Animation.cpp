//
// Created by Brandon Martin on 5/21/19.
//

#include "Animation.h"
#include "Frame.h"
#include "Cursen/Events/AlarmManager.h"

namespace cursen
{

    Animation::Animation() :
            currentFrame(0), numFrames(0), default_duration(1.0), running(false), paused(false)
    {
    }

    Animation::Animation(size_t num_frames) :
            currentFrame(0), numFrames(0), default_duration(1.0), running(false), paused(false)
    {
        this->frames.reserve(num_frames);
    }

    Frame& Animation::operator[](size_t i)
    {
        return frames[i];
    }

    Frame& Animation::add(Frame::VoidFunction fn)
    {
        frames.push_back(Frame(fn));
        numFrames++;
        return frames.at(numFrames - 1);
    }

    Frame& Animation::add(Frame frame)
    {
        frames.push_back(frame);
        numFrames++;
        return frames.at(numFrames - 1);
    }

    void Animation::removeFrame(size_t i)
    {
        if (i < frames.size())
        {
            frames.erase(frames.begin() + i);
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
        if (!running) {
            running = true;
            currentFrame = 0;

            nextFrame();
        }
    }

    void Animation::stop()
    {
        if (running) {
            animationHandle.cancel();
            running = false;
        }
    }

    void Animation::nextFrame()
    {
        frames[currentFrame]();

        if (running && !paused) {
            double time = frames[currentFrame].getDuration();
            if (time <= 0.0) {
                time = default_duration;
            }

            animationHandle = AlarmManager::SetTimeout(std::bind(&Animation::nextFrame, this), time);
        }

        currentFrame = (currentFrame + 1) % numFrames;
    }

    void Animation::setDuration(double time)
    {
        this->default_duration = time;
    }

    double Animation::getDuration()
    {
        return this->default_duration;
    }

    bool Animation::isRunning()
    {
        return this->running;
    }

    void Animation::pause()
    {
        this->paused = true;
        animationHandle.pause();
    }

    void Animation::resume()
    {
        this->paused = false;
        animationHandle.resume();
    }

}

