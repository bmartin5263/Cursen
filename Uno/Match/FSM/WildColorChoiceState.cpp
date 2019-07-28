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
    DataMessage* msg = new InputWildColorChange(matchForm.getMatch()->getMyId(), CardColor::BLUE);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WildColorChoiceState::pressR(MatchForm& matchForm) const
{
    DataMessage* msg = new InputWildColorChange(matchForm.getMatch()->getMyId(), CardColor::RED);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WildColorChoiceState::pressY(MatchForm& matchForm) const
{
    DataMessage* msg = new InputWildColorChange(matchForm.getMatch()->getMyId(), CardColor::YELLOW);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WildColorChoiceState::pressG(MatchForm& matchForm) const
{
    DataMessage* msg = new InputWildColorChange(matchForm.getMatch()->getMyId(), CardColor::GREEN);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
