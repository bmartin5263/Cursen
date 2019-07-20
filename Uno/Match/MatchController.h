//
// Created by Brandon Martin on 7/5/19.
//

#ifndef CURSEN_MATCHCONTROLLER_H
#define CURSEN_MATCHCONTROLLER_H

class MatchForm;
class MatchController
{

public:

    MatchController() = default;
    virtual ~MatchController() = default;

    void setMatchForm(MatchForm* matchForm) { this->matchForm = matchForm; };
    MatchForm* getMatchForm() { return this->matchForm; }

    // Inputs
    virtual void pressEnter() = 0;


    // Concrete Actions
    virtual void clickCard() = 0;
    virtual void pressDraw() = 0;
    virtual void handleDealCards() = 0;

    virtual void start() = 0;
    virtual void waitToBegin() = 0;

private:

    MatchForm* matchForm;

};


#endif //CURSEN_MATCHCONTROLLER_H
