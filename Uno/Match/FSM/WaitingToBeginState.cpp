//
// Created by Brandon Martin on 7/19/19.
//

#include <Uno/Match/Messages/InputBeginGame.h>
#include "WaitingToBeginState.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Match/Messages/InputDealCards.h"
#include "Uno/Match/Messages/InputDrawCard.h"
#include "Uno/GameObjects/Match.h"

void WaitingToBeginState::pressEnter(MatchForm& matchForm) const
{
    DataMessage* msg = new InputBeginGame(matchForm.getMatch()->getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WaitingToBeginState::pressD(MatchForm& matchForm) const
{
    DataMessage* msg = new InputDrawCard(matchForm.getMatch()->getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void WaitingToBeginState::pressSpace(MatchForm& matchForm) const
{
    //DataMessage* msg = new InputPlayCard(matchForm.getMatch()->getMyId(), matchForm.getSelectedCardIndex());
    //msg->setSendType(SendType::Local);
    //DataManager::PushMessage(msg);
}