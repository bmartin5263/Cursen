//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_MATCHSTATE_H
#define CURSEN_MATCHSTATE_H

#include "Uno/Match/MatchController.h"

class MatchInputState
{

public:

    MatchInputState() = default;
    virtual ~MatchInputState() = default;

    virtual void pressEnter(MatchForm& matchForm) const = 0;
    virtual void pressD(MatchForm& matchForm) const = 0;
    virtual void pressSpace(MatchForm& matchForm) const = 0;
    virtual void pressB(MatchForm& matchForm) const = 0;
    virtual void pressR(MatchForm& matchForm) const = 0;
    virtual void pressY(MatchForm& matchForm) const = 0;
    virtual void pressG(MatchForm& matchForm) const = 0;
    virtual void pressP(MatchForm& matchForm) const = 0;
    virtual void pressAnyOtherButton(MatchForm& matchForm) const = 0;

};

#endif //CURSEN_MATCHSTATE_H
