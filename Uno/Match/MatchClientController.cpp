//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/Match/FSM/MatchFSM.h>
#include "MatchClientController.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Deck.h"
#include "Uno/GameObjects/Match.h"

void MatchClientController::clickCard()
{

}

void MatchClientController::pressDraw()
{

}

void MatchClientController::start()
{
    Match* match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    matchForm->updatePlayers();
    matchForm->setHandName(match->getMyPlayer().getName());
    matchForm->setState(&MatchFSM::animationState);
    getMatchForm()->setConsoleMessage("Receiving Data From Host...");
}

void MatchClientController::pressEnter()
{

}

void MatchClientController::handleDealCards()
{
//    Match* match = getMatchForm()->getMatch();
//    MatchForm* matchForm = getMatchForm();
//    matchForm->updatePlayers();
//    matchForm->setDeckMeterSize(Deck::SIZE);
//    matchForm->setDeckMeterCount(108);
//    matchForm->setHandName(match->getMyPlayer().getName());
//    matchForm->setState(&MatchFSM::animationState);
}

void MatchClientController::waitToBegin()
{

}
