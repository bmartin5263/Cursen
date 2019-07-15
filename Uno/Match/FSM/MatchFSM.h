//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_MATCHFSM_H
#define CURSEN_MATCHFSM_H


#include "WaitingToDealCardsState.h"
#include "AnimationState.h"

class MatchFSM
{

public:

    static const WaitingToDealCardsState waitingToDealCardsState;
    static const AnimationState animationState;

};


#endif //CURSEN_MATCHFSM_H
