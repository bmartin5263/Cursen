//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_MATCHSTATE_H
#define CURSEN_MATCHSTATE_H

#include "Uno/Match/MatchController.h"

class MatchState
{

public:

    MatchState() = default;
    virtual ~MatchState() = default;

    virtual void pressEnter(MatchForm& matchForm) const = 0;

};

#endif //CURSEN_MATCHSTATE_H
