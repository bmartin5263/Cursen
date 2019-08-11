//
// Created by Brandon Martin on 7/19/19.
//

#include <Uno/Match/Messages/InputBeginGame.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include "WaitingToBeginState.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Match/Messages/InputDealCards.h"
#include "Uno/Match/Messages/InputDrawCard.h"
#include "Uno/GameObjects/Match.h"

void WaitingToBeginState::pressEnter(MatchForm& matchForm) const
{
    DataMessage* msg = new InputBeginGame(matchForm.getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WaitingToBeginState::pressD(MatchForm& matchForm) const
{
    // Do Noting
}

void WaitingToBeginState::pressSpace(MatchForm& matchForm) const
{
    // Do Nothing
}

void WaitingToBeginState::pressB(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToBeginState::pressR(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToBeginState::pressY(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToBeginState::pressG(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}
