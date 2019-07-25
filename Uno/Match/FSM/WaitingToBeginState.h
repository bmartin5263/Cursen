//
// Created by Brandon Martin on 7/19/19.
//

#ifndef CURSEN_WAITINGTOBEGINSTATE_H
#define CURSEN_WAITINGTOBEGINSTATE_H


#include "MatchState.h"

class WaitingToBeginState : public MatchState
{
public:

    void pressEnter(MatchForm& matchForm) const override;
    void pressD(MatchForm& matchForm) const override;
    void pressSpace(MatchForm& matchForm) const override;

};


#endif //CURSEN_WAITINGTOBEGINSTATE_H
