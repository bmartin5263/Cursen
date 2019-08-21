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
    void handleDealCards() override;
    void waitToBegin() override;
    void reset() override;
    void updateMatch(ClientMatch clientMatch) override;
    void handleRequestMatch(int id, int sock) override;
    void wildChoice(CardColor color) override;
    void handleDisconnect(int sock) override;
    void handleClose(std::string message, bool kicked) override;
    void handleAITurn() override;
    void passTurn() override;
    void gameover(int winner) override;
    void handleGameOver(const Match& final_match_state, int winner) override;

private:

    void checkReadyToStart();

    bool players_connected[4];

};


#endif //CURSEN_MATCHHOSTCONTROLLER_H
