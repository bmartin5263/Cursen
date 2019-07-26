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
            default_duration(1.0), currentFrame(0), numFrames(0), loops(0), loop_counter(0), running(false),
            paused(false), variable_time(true)
    {
    }

    Animation::Animation(size_t num_frames) :
            default_duration(1.0), currentFrame(0), numFrames(0), loops(0), loop_counter(0), running(false),
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

    void Animation::start(bool callFirstFrame)
    {
        // TODO callFirstFrame seems jank, better way?
        if (!running) {
            running = true;
            currentFrame = 0;
            loop_counter = 0;

            if (!variable_time)
            {
                animationHandle = AlarmManager::SetInterval([&]() { this->nextFrame(); }, default_duration);
            }
            else
            {
                if (callFirstFrame) nextFrame();
                else animationHandle = AlarmManager::SetTimeout([&]() { this->nextFrame(); }, frames[frames.size() - 1].getDuration());
            }

        }
    }

    void Animation::stop()
    {
        if (running) {
            animationHandle.cancel();
            end();
        }
    }

    void Animation::nextFrame()
    {
        callCurrentFrame();
        double time = frames[currentFrame].getDuration();
        if (time <= 0.0)
        {
            time = default_duration;
        }
        currentFrame = (currentFrame + 1) % numFrames;

        if (running && !paused)
        {
            if (variable_time)
            {
                animationHandle = AlarmManager::SetTimeout([&]() { this->nextFrame(); }, time);
            }

            if (currentFrame == 0 && loops > 0)
            {
                if (loop_counter >= loops)
                {
                    stop();
                    callOnEnd();
                }
                else
                {
                    loop_counter++;
                }
            }
        }
    }

    void Animation::setFrameDuration(double time)
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
        detachOnEnd();
        detachOnPause();
        detachOnStop();
    }

    void Animation::onStop(Animation::VoidFunction f)
    {
        f_stop = f;
    }

    void Animation::onPause(Animation::VoidFunction f)
    {
        f_pause = f;
    }

    void Animation::onEnd(Animation::VoidFunction f)
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

    void Animation::detachOnEnd()
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

    void Animation::callOnEnd()
    {
        if (f_end) f_end();
    }

    void Animation::end()
    {
        this->running = false;
        this->paused = false;
    }

    void Animation::callCurrentFrame()
    {
        frames[currentFrame]();
    }

}

