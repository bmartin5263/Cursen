//
// Created by Brandon Martin on 7/5/19.
//

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

}

void MatchLocalController::pressDraw()
{

}

void MatchLocalController::start()
{
    Match* match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    Deck& deck = match->getDeck();
    Deck::InitializeDeck(deck);
    matchForm->updatePlayers();
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(deck.size());
    matchForm->setHandName(match->getMyPlayer().getName());
    matchForm->setState(&MatchFSM::waitingToDealCardsState);
}

void MatchLocalController::pressEnter()
{
}

void MatchLocalController::handleDealCards()
{
    getMatchForm()->dealCards();
}

void MatchLocalController::waitToBegin()
{
    MatchForm* matchForm = getMatchForm();
    std::string name = matchForm->getMatch()->getCurrentPlayerName();
    matchForm->setConsoleMessage("First Turn will be " + name + ". Press Enter To Begin.");
    matchForm->setState(&MatchFSM::waitingToBeginState);
}
