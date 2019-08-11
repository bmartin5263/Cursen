//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCONTROLLER_H
#define CURSEN_MATCHCONTROLLER_H

#include <Uno/GameObjects/ClientMatch.h>

class MatchForm;
class MatchController
{

public:

    MatchController() = default;
    virtual ~MatchController() = default;

    void setMatchForm(MatchForm* matchForm) { this->matchForm = matchForm; };
    MatchForm* getMatchForm() { return this->matchForm; }

    virtual void reset() = 0;

    // Inputs
    virtual void pressEnter() = 0;

    virtual void sendIllegalAction(const std::string& msg) = 0;

    // Concrete Actions
    virtual void clickCard() = 0;
    virtual void pressDraw() = 0;
    virtual void wildChoice(CardColor color) = 0;

    // Connection
    virtual void handleDisconnect(int sock) = 0;
    virtual void handleClose(std::string message, bool kicked) = 0;

    virtual void handleDealCards() = 0;
    virtual void handleAITurn() = 0;

    virtual void start() = 0;
    virtual void waitToBegin() = 0;

    virtual void updateMatch(ClientMatch clientMatch) = 0;
    virtual void handleRequestMatch(int id, int sock) = 0;

private:

    MatchForm* matchForm;

};


#endif //CURSEN_MATCHCONTROLLER_H
