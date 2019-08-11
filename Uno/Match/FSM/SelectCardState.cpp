//
// Created by Brandon Martin on 7/28/19.
//

#include <Uno/Messages/DataMessage.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputDrawCard.h>
#include "SelectCardState.h"

void SelectCardState::pressEnter(MatchForm& matchForm) const
{

}

void SelectCardState::pressD(MatchForm& matchForm) const
{
    matchForm.getController()->pressDraw();
}

void SelectCardState::pressSpace(MatchForm& matchForm) const
{
    matchForm.getController()->clickCard();
}

void SelectCardState::pressB(MatchForm& matchForm) const
{

}

void SelectCardState::pressR(MatchForm& matchForm) const
{

}

void SelectCardState::pressY(MatchForm& matchForm) const
{

}

void SelectCardState::pressG(MatchForm& matchForm) const
{

}

void SelectCardState::pressP(MatchForm& matchForm) const
{
    matchForm.getController()->passTurn();
}
