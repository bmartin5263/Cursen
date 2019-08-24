//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/Match/FSM/MatchFSM.h>
#include <Uno/Messages/DataMessage.h>
#include <Uno/Match/Messages/RequestMatchData.h>
#include <Uno/Match/Messages/InputDealCards.h>
#include <Uno/Match/Messages/InputDrawCard.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputWildColorChange.h>
#include <Uno/Match/Messages/InputPass.h>
#include "MatchClientController.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Deck.h"
#include "Uno/GameObjects/Match.h"

using namespace cursen;

void MatchClientController::clickCard()
{
    DataMessage* msg = new InputPlayCard(getMatchForm()->getMatch().getMyId(), getMatchForm()->getSelectedCardIndex());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void MatchClientController::pressDraw()
{
    DataMessage* msg = new InputDrawCard(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void MatchClientController::start()
{
    Match& match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    //matchForm->updatePlayers();
    //matchForm->setHandName(match.getMyPlayer().getName());
    matchForm->setState(&MatchFSM::animationState);
    getMatchForm()->setConsoleMessage("Receiving Data From Host...");

    //std::this_thread::sleep_for(std::chrono::seconds(3));

    DataMessage* msg = new RequestMatchData(match.getMyId());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void MatchClientController::handleDealCards()
{
    assert(false);
}

void MatchClientController::waitToBegin()
{
    MatchForm* matchForm = getMatchForm();
    std::string name = matchForm->getMatch().getCurrentPlayerName();
    matchForm->setConsoleMessage("First Turn will be " + name + ". Waiting For Host to Start.");
}

void MatchClientController::reset()
{
    waitingForMatch = false;
    requestMatchHandle = AlarmHandle();
}

void MatchClientController::updateMatch(ClientMatch clientMatch)
{
    waitingForMatch = false;
    MatchForm* matchForm = getMatchForm();
    Match& match = matchForm->getMatch();
    matchForm->getMatch().readFromClientMatch(clientMatch);
    matchForm->setConsoleMessage("Waiting For Host to Start Game...");
    matchForm->updatePlayers();
    for (int i = 0; i < match.getNumPlayers(); ++i)
    {
        matchForm->getPlayerTile(i).setCardCount(0);
    }
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(Deck::SIZE);
    matchForm->setHandName(match.getMyPlayer().getName());
}

void MatchClientController::handleRequestMatch(int id, int sock)
{
    assert(false);
}

void MatchClientController::wildChoice(CardColor color)
{
    DataMessage* msg = new InputWildColorChange(getMatchForm()->getMatch().getMyId(), color);
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void MatchClientController::handleDisconnect(int sock)
{
    handleClose("Lost Connection to Host :,(", true);
}

void MatchClientController::handleClose(std::string message, bool kicked)
{
    getMatchForm()->exit(message, kicked);
}

void MatchClientController::handleAITurn()
{
}

void MatchClientController::passTurn()
{
    DataMessage* msg = new InputPass(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void MatchClientController::startGameoverEvent(int winner)
{
    // Do Nothing
}

void MatchClientController::handleGameOver(const Match& final_match_state, int winner)
{
    auto matchForm = getMatchForm();
    matchForm->setState(&MatchFSM::animationState);
    matchForm->getMatch() = final_match_state;
    matchForm->runWinnerAnimation(winner);
}

void MatchClientController::handlePostPointTally(int winner, int points_won)
{
    auto matchForm = getMatchForm();
    auto& winning_player = matchForm->getMatch().getPlayer(winner);
    winning_player.addPoints(points_won);
    std::string winner_name = winning_player.getName();
    matchForm->setConsoleMessage(winner_name + " won " + std::to_string(points_won) + " points! Waiting for Host to End Game");
    matchForm->setState(&MatchFSM::animationState);
}

void MatchClientController::endGame()
{
    // Client can't end game
}
