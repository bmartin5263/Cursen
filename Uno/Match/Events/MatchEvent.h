//
// Created by Brandon Martin on 8/26/19.
//

#ifndef CURSEN_MATCHEVENT_H
#define CURSEN_MATCHEVENT_H

class MatchEvent
{

public:

    virtual ~MatchEvent() = default;
    virtual void execute(MatchForm* match_form) = 0;

private:


};

#endif //CURSEN_MATCHEVENT_H
