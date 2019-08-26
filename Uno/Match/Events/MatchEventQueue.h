//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_MATCHEVENTQUEUE_H
#define CURSEN_MATCHEVENTQUEUE_H

#include <queue>

class MatchEvent;
class MatchForm;
class MatchEventQueue
{

public:

    MatchEventQueue(MatchForm* match_form);

    void pushEvent(MatchEvent* event);
    void executeFrontEvent();
    void popEvent();
    size_t size();

private:

    MatchForm* match_form;
    std::queue<MatchEvent*> queue;

};


#endif //CURSEN_MATCHEVENTQUEUE_H
