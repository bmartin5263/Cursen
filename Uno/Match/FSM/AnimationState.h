//
// Created by Brandon Martin on 7/14/19.
//

#ifndef CURSEN_ANIMATIONSTATE_H
#define CURSEN_ANIMATIONSTATE_H

#include "MatchInputState.h"

class AnimationState : public MatchInputState
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


#endif //CURSEN_ANIMATIONSTATE_H
