//
// Created by Brandon Martin on 7/14/19.
//

#ifndef CURSEN_ANIMATIONSTATE_H
#define CURSEN_ANIMATIONSTATE_H

#include "MatchState.h"

class AnimationState : public MatchState
{
public:

    void pressEnter(MatchForm& matchForm) const override;
    void pressD(MatchForm& matchForm) const override;
    void pressSpace(MatchForm& matchForm) const override;
    void pressB(MatchForm& matchForm) const override;
    void pressR(MatchForm& matchForm) const override;
    void pressY(MatchForm& matchForm) const override;
    void pressG(MatchForm& matchForm) const override;

};


#endif //CURSEN_ANIMATIONSTATE_H
