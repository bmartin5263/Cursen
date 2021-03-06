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
#include <Uno/Match/Messages/InputPass.h>
#include <Uno/Match/Messages/InputGameOver.h>
#include <Uno/Match/Messages/InputEndGame.h>
#include "Uno/Forms/MatchForm.h"
#include "MatchHostController.h"

void MatchHostController::clickCard()
{
    DataMessage* msg = new InputPlayCard(getMatchForm()->getMatch().getMyId(), getMatchForm()->getSelectedCardIndex());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::pressDraw()
{
    DataMessage* msg = new InputDrawCard(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::start()
{
    Match& match = getMatchForm()->getMatch();
    MatchForm* matchForm = getMatchForm();
    Deck& deck = match.getDeck();
    Deck::InitializeDeck(deck, (size_t)match.getNumPlayers());
    matchForm->updatePlayers();
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(deck.size());
    matchForm->setHandName(match.getMyPlayer().getName());
    matchForm->setState(&MatchFSM::animationState);
    matchForm->dealInitialCards();
    getMatchForm()->setConsoleMessage("Waiting for Clients...");
    players_connected[0] = true; // host is always player 0
    Player* players = match.getPlayers();
    for (int i = 1; i < match.getNumPlayers(); ++i)
    {
        if (players[i].isAI())
        {
            players_connected[i] = true;
        }
    }
    checkReadyToStart();
}

void MatchHostController::handleDealCards()
{
    DataMessage* msg = new InputDealCards(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::waitToBegin()
{
    MatchForm* matchForm = getMatchForm();
    std::string name = matchForm->getMatch().getCurrentPlayerName();
    matchForm->setConsoleMessage("First Turn will be " + name + ". Press Any Key To Begin.");
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
    Match& match = getMatchForm()->getMatch();

    ClientMatch clientMatch = match.convertToClientMatch(id);
    DataMessage* msg = new ClientMatchUpdate(clientMatch);
    msg->setSendType(SendType::Network);
    msg->setRecipient(sock);
    msg->setRecipientType(RecipientType::Single);
    DataManager::PushMessage(msg);

    int index = getMatchForm()->getMatch().getIndex(id);
    players_connected[index] = true;

    checkReadyToStart();
}

void MatchHostController::wildChoice(CardColor color)
{
    DataMessage* msg = new InputWildColorChange(getMatchForm()->getMatch().getMyId(), color);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::handleDisconnect(int sock)
{

}

void MatchHostController::handleClose(std::string message, bool kicked)
{
    getMatchForm()->exit(message, kicked);
}

void MatchHostController::checkReadyToStart()
{
    bool ready_to_start = true;
    for (int i = 0; i < getMatchForm()->getMatch().getNumPlayers(); ++i)
    {
        if (!players_connected[i])
            ready_to_start = false;
    }
    if (ready_to_start)
    {
        getMatchForm()->setState(&MatchFSM::waitingToDealCardsState);
        getMatchForm()->setConsoleMessage("Clients Connected. Press Any Key to Deal Cards");
    }
}

void MatchHostController::handleAITurn()
{
    MatchForm* matchForm = getMatchForm();
    Match& match = matchForm->getMatch();
    Player& ai_player = match.getCurrentPlayer();
    if (match.isWildCard())
    {
        DataMessage* msg = new InputWildColorChange(match.getCurrentTurnId(), ai_player.getWildColor());
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);
    }
    else
    {
        int card_index = ai_player.getPlayableCardIndex(match.getPile().peekCard());
        if (card_index != -1)
        {
            DataMessage* msg = new InputPlayCard(match.getCurrentTurnId(), card_index);
            msg->setSendType(SendType::Local);
            DataManager::PushMessage(msg);
        }
        else
        {
            if (match.getDeckSize() > 0)
            {
                DataMessage* msg = new InputDrawCard(match.getCurrentTurnId());
                msg->setSendType(SendType::Local);
                DataManager::PushMessage(msg);
            }
            else
            {
                DataMessage* msg = new InputPass(match.getCurrentTurnId());
                msg->setSendType(SendType::Local);
                DataManager::PushMessage(msg);
            }
        }
    }
}

void MatchHostController::passTurn()
{
    DataMessage* msg = new InputPass(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::startGameoverEvent(int winner)
{
    DataMessage* msg = new InputGameOver(winner);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchHostController::handleGameOver(const Match& final_match_state, int winner)
{
    auto matchForm = getMatchForm();
    matchForm->setState(&MatchFSM::animationState);
    //matchForm->getMatch() = final_match_state;
    matchForm->runWinnerAnimation(winner);
}

void MatchHostController::handlePostPointTally(int winner, int points_won)
{
    auto matchForm = getMatchForm();
    auto& winning_player = matchForm->getMatch().getPlayer(winner);
    winning_player.addPoints(points_won);
    std::string winner_name = winning_player.getName();
    matchForm->setConsoleMessage(winner_name + " won " + std::to_string(points_won) + " points! Press Any Key to End Game");
    matchForm->setState(&MatchFSM::gameoverState);
}

void MatchHostController::endGame()
{
    DataMessage* msg = new InputEndGame;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
