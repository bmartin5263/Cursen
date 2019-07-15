//
// Created by Brandon Martin on 7/13/19.
//

#include "WaitingToDealCardsState.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Match/Messages/InputDealCards.h"
#include "Uno/GameObjects/Match.h"

void WaitingToDealCardsState::pressEnter(MatchForm& form) const
{
    DataMessage* msg = new InputDealCards(form.getMatch()->getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
