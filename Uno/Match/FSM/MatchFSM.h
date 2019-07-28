//
// Created by Brandon Martin on 7/13/19.
//

#ifndef CURSEN_MATCHFSM_H
#define CURSEN_MATCHFSM_H


#include "WaitingToDealCardsState.h"
#include "AnimationState.h"
#include "WaitingToBeginState.h"
#include "WildColorChoiceState.h"

class MatchFSM
{

public:

    static const WaitingToDealCardsState waitingToDealCardsState;
    static const WaitingToBeginState waitingToBeginState;
    static const AnimationState animationState;
    static const WildColorChoiceState wildColorChoiceState;

};


#endif //CURSEN_MATCHFSM_H
