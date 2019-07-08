//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHLOCALCONTROLLER_H
#define CURSEN_MATCHLOCALCONTROLLER_H

#include "MatchController.h"

class MatchLocalController : public MatchController
{
public:

    MatchLocalController() = default;
    void clickCard() override;
    void pressDraw() override;
    void start() override;

};


#endif //CURSEN_MATCHLOCALCONTROLLER_H
