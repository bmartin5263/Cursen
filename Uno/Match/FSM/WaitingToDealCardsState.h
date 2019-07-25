//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_WAITINGTOBEGIN_H
#define CURSEN_WAITINGTOBEGIN_H


#include "MatchState.h"

class WaitingToDealCardsState : public MatchState
{
public:

    void pressEnter(MatchForm& controller) const override;
    void pressD(MatchForm& matchForm) const override;
    void pressSpace(MatchForm& matchForm) const override;

};


#endif //CURSEN_WAITINGTOBEGIN_H
