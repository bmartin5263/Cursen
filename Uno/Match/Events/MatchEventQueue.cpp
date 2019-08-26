//
// Created by Brandon Martin on 8/26/19.
//

#include <cassert>
#include "MatchEventQueue.h"
#include "MatchEvent.h"

MatchEventQueue::MatchEventQueue(MatchForm* match_form) :
    match_form(match_form)
{

}


void MatchEventQueue::pushEvent(MatchEvent* event)
{
    queue.push(event);
    if (size() == 1) executeFrontEvent();
}

void MatchEventQueue::executeFrontEvent()
{
    assert(size() > 0);
    MatchEvent* event = queue.front();
    event->execute(match_form);
}

size_t MatchEventQueue::size()
{
    return queue.size();
}

void MatchEventQueue::popEvent()
{
    assert(size() > 0);
    MatchEvent* event = queue.front();
    queue.pop();
    delete event;
    if (size() > 0) executeFrontEvent();
}