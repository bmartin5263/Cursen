//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/Match/Messages/InputDrawCard.h>
#include <Uno/Match/Messages/InputPlayCard.h>
#include <Uno/Match/Messages/InputWildColorChange.h>
#include <Uno/Match/Messages/InputPass.h>
#include <Uno/Match/Messages/InputGameOver.h>
#include <Uno/Match/Messages/InputEndGame.h>
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
    Deck::InitializeDeck(deck, (size_t)match.getNumPlayers());
    matchForm->updatePlayers();
    matchForm->setDeckMeterSize(Deck::SIZE);
    matchForm->setDeckMeterCount(deck.size());
    matchForm->setHandName(match.getMyPlayer().getName());
    matchForm->dealInitialCards();
    matchForm->setConsoleMessage("Press Any Key to Deal Cards");
    matchForm->setState(&MatchFSM::waitingToDealCardsState);
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
    matchForm->setConsoleMessage("First Turn will be " + name + ". Press Any Key To Begin.");
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
    getMatchForm()->exit(message, kicked);
}

void MatchLocalController::handleAITurn()
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

void MatchLocalController::passTurn()
{
    DataMessage* msg = new InputPass(getMatchForm()->getMatch().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::startGameoverEvent(int winner)
{
    DataMessage* msg = new InputGameOver(winner);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void MatchLocalController::handleGameOver(const Match& final_match_state, int winner)
{
    auto matchForm = getMatchForm();
    matchForm->setState(&MatchFSM::animationState);
    matchForm->getMatch() = final_match_state;
    matchForm->runWinnerAnimation(winner);
}

void MatchLocalController::handlePostPointTally(int winner, int points_won)
{
    auto matchForm = getMatchForm();
    auto& winning_player = matchForm->getMatch().getPlayer(winner);
    winning_player.addPoints(points_won);
    std::string winner_name = winning_player.getName();
    matchForm->setConsoleMessage(winner_name + " won " + std::to_string(points_won) + " points! Press Any Key to End Game");
    matchForm->setState(&MatchFSM::gameoverState);
}

void MatchLocalController::endGame()
{
    DataMessage* msg = new InputEndGame;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
