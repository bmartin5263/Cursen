//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCLIENTCONTROLLER_H
#define CURSEN_MATCHCLIENTCONTROLLER_H

#include <Cursen/Events/AlarmHandle.h>
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
    void waitToBegin() override;
    void reset() override;
    void updateMatch(ClientMatch clientMatch) override;
    void handleRequestMatch(int id, int sock) override;
    void wildChoice(CardColor color) override;
    void handleDisconnect(int sock) override;
    void handleClose(std::string message, bool kicked) override;
    void handleAITurn() override;

private:

    cursen::AlarmHandle requestMatchHandle;
    bool waitingForMatch;

};


#endif //CURSEN_MATCHCLIENTCONTROLLER_H
