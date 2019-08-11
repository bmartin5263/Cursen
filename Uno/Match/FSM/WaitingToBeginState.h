//
// Created by Brandon Martin on 7/19/19.
//

#ifndef CURSEN_WAITINGTOBEGINSTATE_H
#define CURSEN_WAITINGTOBEGINSTATE_H


#include "MatchInputState.h"

class WaitingToBeginState : public MatchInputState
{
public:

    void pressEnter(MatchForm& matchForm) const override;
    void pressD(MatchForm& matchForm) const override;
    void pressSpace(MatchForm& matchForm) const override;
    void pressB(MatchForm& matchForm) const override;
    void pressR(MatchForm& matchForm) const override;
    void pressY(MatchForm& matchForm) const override;
    void pressG(MatchForm& matchForm) const override;
    void pressP(MatchForm& matchForm) const override;

};


#endif //CURSEN_WAITINGTOBEGINSTATE_H
