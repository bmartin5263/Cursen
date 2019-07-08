//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCONTROLLER_H
#define CURSEN_MATCHCONTROLLER_H

#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"

class MatchController
{

public:

    MatchController() = default;
    virtual ~MatchController() = default;

    void setMatchForm(MatchForm* matchForm) { this->matchForm = matchForm; };
    MatchForm* getMatchForm() { return this->matchForm; }

    virtual void clickCard() = 0;
    virtual void pressDraw() = 0;

    virtual void start() = 0;

private:

    MatchForm* matchForm;

};


#endif //CURSEN_MATCHCONTROLLER_H
