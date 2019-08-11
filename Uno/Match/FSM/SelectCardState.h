//
// Created by Brandon Martin on 7/28/19.
//

#ifndef CURSEN_SELECTCARDSTATE_H
#define CURSEN_SELECTCARDSTATE_H


#include "MatchInputState.h"

class SelectCardState : public MatchInputState
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


#endif //CURSEN_SELECTCARDSTATE_H
