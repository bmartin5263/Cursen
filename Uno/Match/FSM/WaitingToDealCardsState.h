//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_WAITINGTOBEGIN_H
#define CURSEN_WAITINGTOBEGIN_H


#include "MatchInputState.h"

class WaitingToDealCardsState : public MatchInputState
{
public:

    void pressEnter(MatchForm& controller) const override;
    void pressD(MatchForm& matchForm) const override;
    void pressSpace(MatchForm& matchForm) const override;
    void pressB(MatchForm& matchForm) const override;
    void pressR(MatchForm& matchForm) const override;
    void pressY(MatchForm& matchForm) const override;
    void pressG(MatchForm& matchForm) const override;
    void pressP(MatchForm& matchForm) const override;
    void pressAnyOtherButton(MatchForm& matchForm) const override;

};


#endif //CURSEN_WAITINGTOBEGIN_H
