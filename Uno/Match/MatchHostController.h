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
    void reset() override;
    void updateMatch(ClientMatch clientMatch) override;
    void handleRequestMatch(int id, int sock) override;
    void wildChoice(CardColor color) override;

private:

    bool players_connected[4];

};


#endif //CURSEN_MATCHHOSTCONTROLLER_H
