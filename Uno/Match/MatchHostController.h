//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHHOSTCONTROLLER_H
#define CURSEN_MATCHHOSTCONTROLLER_H

#include "MatchController.h"

class MatchHostController : public MatchController
{
public:

    MatchHostController() = default;
    void clickCard() override;
    void pressDraw() override;
    void start() override;
    void pressEnter() override;
    void handleDealCards() override;
    void waitToBegin() override;

};


#endif //CURSEN_MATCHHOSTCONTROLLER_H