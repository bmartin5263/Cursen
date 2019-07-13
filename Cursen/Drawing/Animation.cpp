//
// Created by Brandon Martin on 5/21/19.
//

#include <cassert>
#include "Animation.h"
#include "Frame.h"
#include "Cursen/Events/AlarmManager.h"

namespace cursen
{

    Animation::Animation() :
            currentFrame(0), numFrames(0), default_duration(1.0), loops(0), loop_counter(0), running(false),
            paused(false), variable_time(true)
    {
    }

    Animation::Animation(size_t num_frames) :
            currentFrame(0), numFrames(0), default_duration(1.0), loops(0), loop_counter(0), running(false),
            paused(false), variable_time(true)
    {
        this->frames.reserve(num_frames);
    }

    Frame& Animation::operator[](size_t i)
    {
        return frames[i];
    }

    Frame& Animation::add(VoidFunction fn)
    {
        frames.push_back(Frame(fn, this));
        numFrames++;
        return frames.at(numFrames - 1);
    }

    Frame& Animation::add(Frame frame)
    {
        frame.setParent(this);
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
            loop_counter = 0;

            nextFrame();
            if (!variable_time)
            {
                animationHandle = AlarmManager::SetInterval(std::bind(&Animation::nextFrame, this), default_duration);
            }

        }
    }

    void Animation::stop()
    {
        if (running) {
            animationHandle.cancel();
            running = false;
            paused = false;
        }
    }

    void Animation::nextFrame()
    {
        frames[currentFrame]();

        if (running && !paused)
        {
            if (variable_time)
            {
                double time = frames[currentFrame].getDuration();
                if (time <= 0.0)
                {
                    time = default_duration;
                }

                animationHandle = AlarmManager::SetTimeout(std::bind(&Animation::nextFrame, this), time);
            }

            currentFrame = (currentFrame + 1) % numFrames;
            if (currentFrame == 0) loop_counter++;

            if (loops > 0 && loop_counter >= loops) stop();
        }
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
        if (!paused)
        {
            this->paused = true;
            animationHandle.pause();
        }
    }

    void Animation::resume()
    {
        if (paused)
        {
            this->paused = false;
            this->animationHandle.resume();
        }
    }

    void Animation::setVariableTime(bool value)
    {
        assert(!running);
        this->variable_time = value;
    }

    void Animation::setLoops(size_t count)
    {
        this->loops = count;
    }

    size_t Animation::getLoops()
    {
        return this->loops;
    }

    void Animation::clear()
    {
        if (running)
        {
            stop();
        }
        this->loops = 0;
        this->numFrames = 0;
        this->paused = false;
        this->loop_counter = 0;
        this->currentFrame = 0;
        this->frames.clear();
    }

    void Animation::onStop(Animation::VoidFunction& f)
    {
        f_stop = f;
    }

    void Animation::onPause(Animation::VoidFunction& f)
    {
        f_pause = f;
    }

    void Animation::onLoopEnd(Animation::VoidFunction& f)
    {
        f_end = f;
    }

    void Animation::detachOnStop()
    {
        f_stop = 0;
    }

    void Animation::detachOnPause()
    {
        f_pause = 0;
    }

    void Animation::detachOnLoopEnd()
    {
        f_end = 0;
    }

    void Animation::callOnStop()
    {
        if (f_stop) f_stop();
    }

    void Animation::callOnPause()
    {
        if (f_pause) f_pause();
    }

    void Animation::callOnLoopEnd()
    {
        if (f_end) f_end();
    }

}

