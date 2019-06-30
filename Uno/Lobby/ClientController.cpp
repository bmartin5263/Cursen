//
// Created by Brandon Martin on 5/20/19.
//

#include <Uno/Network/NetworkManager.h>
#include <Uno/Network/Client.h>
#include "ClientController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Constants.h"
#include "Uno/Messages/InputChat.h"
#include "Uno/Messages/InputCloseRoom.h"

ClientController::ClientController(LobbyForm* form) : LobbyController(form)
{

}

void ClientController::initialize()
{
    lobbyForm->initializeForClient();
}

void ClientController::destroy()
{
    lobbyForm->leaveClient(std::string(), false);
}

void ClientController::clickStart()
{
    throw std::logic_error("Client cannot start game.");
}

void ClientController::clickAddAI()
{
    throw std::logic_error("Client cannot add AI.");
}

void ClientController::clickSearch()
{
    throw std::logic_error("Client cannot search.");
}

void ClientController::clickClose()
{
    //DataMessage* msg = new InputCloseRoom(lobbyForm->getLobby().getMyId());
    //msg->setSendType(SendType::Local);
    //DataManager::PushMessage(msg);
    ((Client&)NetworkManager::GetDevice()).closeConnection();
}

void ClientController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void ClientController::sendChat()
{
    ChatBox& chatBox = lobbyForm->getChatBox();

    std::string text = Constants::rtrim(chatBox.getMessage());
    if (!text.empty())
    {
        DataMessage* msg = new InputChat(lobbyForm->getLobby().getMyId(), text);
        msg->setSendType(SendType::Network);
        DataManager::PushMessage(msg);

        chatBox.clearMessage();
    }
    else
    {
        lobbyForm->stopChat();
    }
}

void ClientController::selectPlayerToKick(int id)
{
    throw std::logic_error("Client cannot kick players.");
}

void ClientController::handleClose(std::string msg, bool kicked)
{
    lobbyForm->leaveClient(msg, kicked);
}

void ClientController::handleStartSearch()
{
    lobbyForm->getLobby().startSearch();
    lobbyForm->getPlayerStaging().startSearching();
}

void ClientController::handleStopSearch()
{
    lobbyForm->getLobby().stopSearch();
    lobbyForm->getPlayerStaging().stopSearching();
}

void ClientController::handleAddAi(Player new_ai)
{
    lobbyForm->getLobby().addPlayer(new_ai);
    lobbyForm->getConsole().setMessage("Welcome, " + new_ai.getName() + "!");

    if (lobbyForm->getLobby().isSearching() && lobbyForm->getLobby().getNumPlayers() >= Lobby::MAX_PLAYERS)
    {
        handleStopSearch();
    }
}

void ClientController::handleKickPlayer(int id)
{
    lobbyForm->kickPlayer(id);
}

void ClientController::sendKickMessages(int id)
{
    //(void*)id;
    assert(false);
}

void ClientController::handleDisconnect(int sock)
{
    handleClose("Host Connection Lost!", true);
}

void ClientController::sendCloseMessages()
{
    assert(false);
}
