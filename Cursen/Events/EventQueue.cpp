//
// Created by Brandon Martin on 3/23/19.
//

#include "EventQueue.h"

Event EventQueue::pop() {
    std::lock_guard<std::mutex> locker(mu);
    Event event;
    event = eventQueue.front();
    eventQueue.pop();
    return event;
}

void EventQueue::push(Event event) {
    std::lock_guard<std::mutex> locker(mu);
    eventQueue.push(event);
    cond.notify_one();
}

void EventQueue::wait() {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, [&]() {return !eventQueue.empty(); });
}

bool EventQueue::isEmpty() {
    std::lock_guard<std::mutex> locker(mu);
    return eventQueue.empty();
}