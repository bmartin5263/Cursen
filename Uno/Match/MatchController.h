//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCONTROLLER_H
#define CURSEN_MATCHCONTROLLER_H

#include <Uno/GameObjects/ClientMatch.h>
#include <Uno/GameObjects/Match.h>

class MatchForm;
class MatchController
{

public:

    MatchController() = default;
    virtual ~MatchController() = default;

    void setMatchForm(MatchForm* matchForm) { this->matchForm = matchForm; };
    MatchForm* getMatchForm() { return this->matchForm; }

    virtual void reset() = 0;

    // Concrete Actions
    virtual void clickCard() = 0;
    virtual void pressDraw() = 0;
    virtual void wildChoice(CardColor color) = 0;
    virtual void passTurn() = 0;
    virtual void gameover(int winner) = 0;

    // Connection
    virtual void handleDisconnect(int sock) = 0;
    virtual void handleClose(std::string message, bool kicked) = 0;

    virtual void handleDealCards() = 0;
    virtual void handleAITurn() = 0;
    virtual void handleGameOver(const Match& final_match_state, int winner) = 0;
    virtual void handlePostPointTally(int winner, int points_won) = 0;

    virtual void start() = 0;
    virtual void waitToBegin() = 0;

    // Match Updates
    virtual void updateMatch(ClientMatch clientMatch) = 0;
    virtual void handleRequestMatch(int id, int sock) = 0;

private:

    MatchForm* matchForm;

};


#endif //CURSEN_MATCHCONTROLLER_H
