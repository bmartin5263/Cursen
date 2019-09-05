//
// Created by Brandon Martin on 5/20/19.
//

#include <Uno/Network/NetworkManager.h>
#include <Uno/Network/Client.h>
#include <Uno/GameObjects/Match.h>
#include <Uno/Forms/MatchForm.h>
#include <Uno/Match/MatchReturnData.h>
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
}


void ClientController::clickStart()
{
    assert(false);
}

void ClientController::clickAddAI()
{
    assert(false);
}

void ClientController::clickSearch()
{
    assert(false);
}

void ClientController::clickClose()
{
    ((Client&)NetworkManager::GetDevice()).closeConnection();
    handleClose("Goodbye!", false);
}

void ClientController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(lobbyForm->getLobby().getMyIndex());
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void ClientController::sendChat()
{
    ChatBox& chatBox = lobbyForm->getChatBox();

    std::string text = Constants::rtrim(chatBox.getMessage());
    if (!text.empty())
    {
        DataMessage* msg = new InputChat(lobbyForm->getLobby().getMyIndex(), text);
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
    assert(false);
}

void ClientController::handleClose(std::string msg, bool kicked)
{
    NetworkManager::Destroy();
    lobbyForm->cleanLobby(msg, kicked);
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

void ClientController::handleEnterMatch()
{
    lobbyForm->stopChat();
    Lobby& lobby = lobbyForm->getLobby();
    Player* players = lobby.getPlayers();
    int num_players = lobby.getNumPlayers();

    int my_id = lobby.getMyId();
    int my_index = -1;
    for (int i = 0; i < num_players; ++i)
    {
        if (players[i].getId() == my_id)
        {
            my_index = i;
        }
    }

    MatchForm* matchForm = new MatchForm(LobbyType::JOIN, Match(players, num_players, my_id, my_index));
    matchForm->onClosed([this](void* return_val)
    {
        assert(return_val != nullptr);
        MatchReturnData* returnData = (MatchReturnData*) return_val;
        if (returnData->kicked)
        {
            handleClose(returnData->message, returnData->kicked);
        }
        else
        {
            lobbyForm->getConsole().setMessage(returnData->message);
            for (int i = 0; i < lobbyForm->getLobby().getNumPlayers(); ++i) lobbyForm->getLobby().getPlayerByIndex(i) = returnData->players[i];
        }
        delete returnData;
    });

    lobbyForm->openForm(matchForm);
}

void ClientController::handleAddPlayer(Player new_player)
{
    lobbyForm->getLobby().addPlayer(new_player);
    if (!new_player.isDummy()) lobbyForm->getConsole().setMessage("Welcome, " + new_player.getName() + "!");
    if (lobbyForm->getLobby().isSearching() && lobbyForm->getLobby().getNumPlayers() >= Lobby::MAX_PLAYERS)
    {
        handleStopSearch();
    }
}

void ClientController::handleRequestJoinLobby(const std::string& name, int sock_fd)
{
    assert(false);
}

void ClientController::handleUpdatePlayer(const Player& player, int index)
{
    Lobby& lobby = lobbyForm->getLobby();
    bool was_dummy = lobby.getPlayerByIndex(index).isDummy();

    lobby.setPlayer(player, index);

    if (was_dummy) lobbyForm->getConsole().setMessage("Welcome, " + player.getName() + "!");
}

void ClientController::handleInputColorChange(int sender)
{
    assert(false);
}
