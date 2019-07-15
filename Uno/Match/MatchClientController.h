//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCLIENTCONTROLLER_H
#define CURSEN_MATCHCLIENTCONTROLLER_H

#include "MatchController.h"

class MatchClientController : public MatchController
{
public:

    MatchClientController() = default;
    void clickCard() override;
    void pressDraw() override;
    void start() override;
    void pressEnter() override;
    void handleDealCards() override;

};


#endif //CURSEN_MATCHCLIENTCONTROLLER_H
