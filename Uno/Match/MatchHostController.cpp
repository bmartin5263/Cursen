//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/GameObjects/Match.h>
#include <Uno/Match/FSM/MatchFSM.h>
#include <Uno/Messages/DataMessage.h>
#include <Uno/Match/Messages/InputDealCards.h>
#include <Uno/Match/Messages/ClientMatchUpdate.h>
#include <Uno/Match/Messages/InputDrawCard.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputWildColorChange.h>
#include "Uno/Forms/MatchForm.h"
#include "MatchHostController.h"

void MatchHostController::clickCard()
{
    DataMessage* msg = new InputPlayCard(getMatchForm()->getMatch()->getMyId(), getMatchForm()->getSelectedCardIndex());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::pressDraw()
{
    DataMessage* msg = new InputDrawCard(getMatchForm()->getMatch()->getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::start()
{
    Match* match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    Deck& deck = match->getDeck();
    Deck::InitializeDeck(deck);
    matchForm->updatePlayers();
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(deck.size());
    matchForm->setHandName(match->getMyPlayer().getName());
    matchForm->setState(&MatchFSM::animationState);
    matchForm->dealInitialCards();
    getMatchForm()->setConsoleMessage("Waiting for Clients...");
    players_connected[0] = true; // host is always player 0
}

void MatchHostController::pressEnter()
{

}

void MatchHostController::handleDealCards()
{
    DataMessage* msg = new InputDealCards(getMatchForm()->getMatch()->getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::waitToBegin()
{
    MatchForm* matchForm = getMatchForm();
    std::string name = matchForm->getMatch()->getCurrentPlayerName();
    matchForm->setConsoleMessage("First Turn will be " + name + ". Press Enter To Begin.");
    matchForm->setState(&MatchFSM::waitingToBeginState);
}

void MatchHostController::reset()
{
    for (int i = 0; i < 4; ++i)
    {
        players_connected[i] = false;
    }
}

void MatchHostController::updateMatch(ClientMatch clientMatch)
{
    // Host Should Not Be Receiving ClientMatches
    assert(false);
}

void MatchHostController::handleRequestMatch(int id, int sock)
{
    Match* match = getMatchForm()->getMatch();

    ClientMatch clientMatch = match->convertToClientMatch(id);
    DataMessage* msg = new ClientMatchUpdate(clientMatch);
    msg->setSendType(SendType::Network);
    msg->setRecipient(sock);
    msg->setRecipientType(RecipientType::Single);
    DataManager::PushMessage(msg);

    int index = getMatchForm()->getMatch()->getIndex(id);
    players_connected[index] = true;

    bool ready_to_start = true;
    for (int i = 0; i < match->getNumPlayers(); ++i)
    {
        if (!players_connected[i]) ready_to_start = false;
    }
    if (ready_to_start)
    {
        getMatchForm()->setState(&MatchFSM::waitingToDealCardsState);
        getMatchForm()->setConsoleMessage("Clients Connected. Press Enter to Deal Cards");
    }
}

void MatchHostController::wildChoice(CardColor color)
{
    DataMessage* msg = new InputWildColorChange(getMatchForm()->getMatch()->getMyId(), color);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::handleDisconnect(int sock)
{

}

void MatchHostController::handleClose(std::string message, bool kicked)
{

}
