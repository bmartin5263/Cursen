//
// Created by Brandon Martin on 5/20/19.
//

#include "LocalController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Messages/InputAddAi.h"
#include "Uno/Messages/InputKick.h"

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

void LocalController::clickKick()
{
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Kick Clicked!");
    lobbyForm->enableRemovePlayerCursor();
}

void LocalController::clickClose()
{
    destroy();
}

void LocalController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(0);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::sendChat()
{
    throw std::logic_error("Local cannot chat.");
}

void LocalController::kickPlayer(int id)
{
    DataMessage* msg = new InputKick(id);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}
