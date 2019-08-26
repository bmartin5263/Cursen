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
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressSpace(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressB(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressR(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressY(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressG(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressP(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}

void WaitingToDealCardsState::pressAnyOtherButton(MatchForm& matchForm) const
{
    matchForm.getController()->handleDealCards();
}
