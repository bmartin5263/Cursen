//
// Created by Brandon Martin on 7/13/19.
//

#include "WaitingToDealCardsState.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Match/Messages/InputDealCards.h"
#include "Uno/GameObjects/Match.h"

void WaitingToDealCardsState::pressEnter(MatchForm& form) const
{
    form.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressD(MatchForm& matchForm) const
{
    // Cannot Draw Cards Before Game Starts
}

void WaitingToDealCardsState::pressSpace(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToDealCardsState::pressB(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToDealCardsState::pressR(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToDealCardsState::pressY(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WaitingToDealCardsState::pressG(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}
