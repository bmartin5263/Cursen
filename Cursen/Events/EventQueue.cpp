//
// Created by Brandon Martin on 3/23/19.
//

#include "EventQueue.h"

void EventQueue::pop(Event &event) {
    std::lock_guard<std::mutex> locker(mu);
    event = eventQueue.front();
    eventQueue.pop();
}

void EventQueue::push(Event event) {
    std::lock_guard<std::mutex> locker(mu);
    eventQueue.push(event);
}

void EventQueue::wait() {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [&]() {return !eventQueue.empty(); });
}