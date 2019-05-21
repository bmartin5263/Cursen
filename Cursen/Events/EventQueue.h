//
// Created by Brandon Martin on 3/23/19.
//

#ifndef CURSEN_EVENTQUEUE_H
#define CURSEN_EVENTQUEUE_H

#include <mutex>
#include <queue>

#include "Event.h"

namespace cursen {

    class EventQueue {

    public:

        EventQueue() = default;
        EventQueue(const EventQueue& other) = delete;
        EventQueue& operator = (const EventQueue& other) = delete;
        ~EventQueue() = default;

        void push(Event event);
        Event pop();
        void wait();
        bool isEmpty();


    private:

        std::queue<Event> eventQueue;
        std::mutex mu;
        std::condition_variable cond;

    };

}


#endif //CURSEN_EVENTQUEUE_H
