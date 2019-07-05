//
// Created by Brandon Martin on 5/20/19.
//

#include "LocalController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Messages/InputAddAi.h"
#include "Uno/Messages/InputKick.h"
#include "Uno/Messages/InputCloseRoom.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Forms/MatchForm.h"

LocalController::LocalController(LobbyForm* form) : LobbyController(form)
{

}

void LocalController::initialize()
{
    lobbyForm->initializeForLocal();
}

void LocalController::destroy()
{
    lobbyForm->leaveLocal();
}


void LocalController::clickStart()
{
    lobbyForm->getConsole().setText("Start Clicked!");
    cursen::CursenApplication::OpenForm(new MatchForm);
}

void LocalController::clickAddAI()
{
    DataMessage* msg = new InputAddAi;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::clickSearch()
{
    throw std::logic_error("Local cannot search.");
}

void LocalController::clickClose()
{
    DataMessage* msg = new InputCloseRoom(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::sendChat()
{
    assert(false);
}

void LocalController::selectPlayerToKick(int id)
{
    DataMessage* msg = new InputKick(id);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::handleClose(std::string msg, bool kicked)
{
    lobbyForm->leaveLocal();
}

void LocalController::handleStartSearch()
{
    assert(false);
}

void LocalController::handleStopSearch()
{
    assert(false);
}

void LocalController::handleAddAi(Player new_ai)
{
    lobbyForm->getLobby().addPlayer(new_ai);
    lobbyForm->getConsole().setMessage("Welcome, " + new_ai.getName() + "!");
}

void LocalController::handleKickPlayer(int id)
{
    lobbyForm->kickPlayer(id);
}

void LocalController::sendKickMessages(int id)
{
    DataMessage* msg = new KickPlayer(id);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::handleDisconnect(int sock)
{
    assert(false);
}

void LocalController::sendCloseMessages()
{
    DataMessage* msg = new CloseRoom("Local Has Closed", false);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
