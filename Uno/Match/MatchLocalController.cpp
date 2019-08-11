//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/Match/Messages/InputDrawCard.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputWildColorChange.h>
#include "Uno/GameObjects/Match.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/Match/FSM/MatchFSM.h"
#include "MatchLocalController.h"
#include "Uno/GameObjects/Deck.h"
#include "Cursen/Events/Event.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Match/Messages/InputDealCards.h"

void MatchLocalController::clickCard()
{
    DataMessage* msg = new InputPlayCard(getMatchForm()->getMatch().getMyId(), getMatchForm()->getSelectedCardIndex());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::pressDraw()
{
    DataMessage* msg = new InputDrawCard(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::start()
{
    Match& match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    Deck& deck = match.getDeck();
    Deck::InitializeDeck(deck);
    matchForm->updatePlayers();
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(deck.size());
    matchForm->setHandName(match.getMyPlayer().getName());
    matchForm->dealInitialCards();
    matchForm->setConsoleMessage("Press Enter to Deal Cards");
    matchForm->setState(&MatchFSM::waitingToDealCardsState);
}

void MatchLocalController::pressEnter()
{
}

void MatchLocalController::handleDealCards()
{
    DataMessage* msg = new InputDealCards(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::waitToBegin()
{
    MatchForm* matchForm = getMatchForm();
    std::string name = matchForm->getMatch().getCurrentPlayerName();
    matchForm->setConsoleMessage("First Turn will be " + name + ". Press Enter To Begin.");
    matchForm->setState(&MatchFSM::waitingToBeginState);
}

void MatchLocalController::reset()
{

}

void MatchLocalController::updateMatch(ClientMatch clientMatch)
{
    assert(false);
}

void MatchLocalController::handleRequestMatch(int id, int sock)
{
    assert(false);
}

void MatchLocalController::wildChoice(CardColor color)
{
    DataMessage* msg = new InputWildColorChange(getMatchForm()->getMatch().getMyId(), color);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::handleDisconnect(int sock)
{

}

void MatchLocalController::handleClose(std::string message, bool kicked)
{

}

void MatchLocalController::handleAITurn()
{
    MatchForm* matchForm = getMatchForm();
    Match& match = matchForm->getMatch();
    Player& ai_player = match.getCurrentPlayer();
    if (match.isWaitingForWildColor())
    {
        DataMessage* msg = new InputWildColorChange(matchForm->getMatch().getCurrentTurnId(), ai_player.getWildColor());
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);
    }
    else
    {
        int card_index = ai_player.getPlayableCard(match.getPile().peekCard());
        if (card_index != -1)
        {
            DataMessage* msg = new InputPlayCard(matchForm->getMatch().getCurrentTurnId(), card_index);
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
        }
        else
        {
            DataMessage* msg = new InputDrawCard(matchForm->getMatch().getCurrentTurnId());
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
        }
    }
}
