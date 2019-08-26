//
// Created by Brandon Martin on 7/27/19.
//

#include "WildColorChoiceState.h"
#include "Uno/Match/Messages/InputWildColorChange.h"

void WildColorChoiceState::pressEnter(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WildColorChoiceState::pressD(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WildColorChoiceState::pressSpace(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WildColorChoiceState::pressB(MatchForm& matchForm) const
{
    matchForm.getController()->wildChoice(CardColor::BLUE);
}

void WildColorChoiceState::pressR(MatchForm& matchForm) const
{
    matchForm.getController()->wildChoice(CardColor::RED);
}

void WildColorChoiceState::pressY(MatchForm& matchForm) const
{
    matchForm.getController()->wildChoice(CardColor::YELLOW);
}

void WildColorChoiceState::pressG(MatchForm& matchForm) const
{
    matchForm.getController()->wildChoice(CardColor::GREEN);
}

void WildColorChoiceState::pressP(MatchForm& matchForm) const
{
    // Do Nothing Intentionally
}

void WildColorChoiceState::pressAnyOtherButton(MatchForm& matchForm) const
{

}
