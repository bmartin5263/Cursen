//
// Created by Brandon Martin on 7/27/19.
//

#ifndef CURSEN_WILDCOLORCHOICESTATE_H
#define CURSEN_WILDCOLORCHOICESTATE_H


#include "MatchInputState.h"

class WildColorChoiceState : public MatchInputState
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
    void pressAnyOtherButton(MatchForm& matchForm) const override;
};


#endif //CURSEN_WILDCOLORCHOICESTATE_H
