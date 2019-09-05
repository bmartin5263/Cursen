//
// Created by Brandon Martin on 5/20/19.
//

#include <Uno/Messages/InputSearch.h>
#include <Uno/GameObjects/Match.h>
#include <Uno/Forms/MatchForm.h>
#include <Uno/Messages/InputEnterMatch.h>
#include <Uno/Match/MatchReturnData.h>
#include <Uno/Messages/AddPlayer.h>
#include <Uno/Messages/LobbyUpdate.h>
#include <Uno/Messages/UpdatePlayer.h>
#include "Uno/Network/Host.h"
#include "Uno/Network/NetworkManager.h"
#include "HostController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Constants.h"
#include "Uno/Messages/InputChat.h"
#include "Uno/Messages/InputAddAi.h"
#include "Uno/Messages/InputKick.h"
#include "Uno/Messages/InputCloseRoom.h"
#include "Uno/Messages/DisconnectFromHost.h"
#include "Uno/GameObjects/Lobby.h"

HostController::HostController(LobbyForm* lobbyForm) : LobbyController(lobbyForm)
{}


void HostController::initialize()
{
    NetworkManager::SetMode(NetworkMode::Host);
    NetworkManager::OnConnect([this](int sock_fd)
    {
        Lobby& lobby = lobbyForm->getLobby();
        int new_player_index = lobby.getNumPlayers();

        putSocket(sock_fd, new_player_index);
        dummy_players.insert(new_player_index);
        Player player_placeholder = lobby.createDummy();

        DataMessage* msg = new AddPlayer(player_placeholder);
        msg->setSendType(SendType::Both);
        msg->setRecipientType(RecipientType::Broadcast_Except_Recipient);
        msg->setRecipient(sock_fd);
        DataManager::PushMessage(msg);
    });
    NetworkManager::OnDisconnect([this](int sock_fd)
    {
        // to be decided
    });
}

void HostController::clickStart()
{
    DataMessage* msg = new InputEnterMatch(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::clickAddAI()
{
    DataMessage* msg = new InputAddAi;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::clickSearch()
{
    DataMessage* msg = new InputSearch;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::clickClose()
{
    DataMessage* msg = new InputCloseRoom(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(lobbyForm->getLobby().getMyIndex());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::sendChat()
{
    ChatBox& chatBox = lobbyForm->getChatBox();

    std::string text = Constants::rtrim(chatBox.getMessage());
    if (!text.empty())
    {
        DataMessage* msg = new InputChat(lobbyForm->getLobby().getMyIndex(), text);
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);

        chatBox.clearMessage();
    }
    else
    {
        lobbyForm->stopChat();
    }
}

void HostController::selectPlayerToKick(int id)
{
    DataMessage* msg = new InputKick(id);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::handleClose(std::string msg, bool kicked)
{
    NetworkManager::Destroy();
    lobbyForm->cleanLobby("Welcome to Uno!", false);
}

void HostController::handleStartSearch()
{
    auto& host_device = (Host&)NetworkManager::GetDevice();
    assert(!host_device.isListening());

    bool success = host_device.startListening();
    assert(success);

    if (success)
    {
        auto& lobby = lobbyForm->getLobby();
        lobby.startSearch();
        lobbyForm->getPlayerStaging().startSearching();
        lobbyForm->getSearchButton().setText("Stop Search");
        lobbyForm->getConsole().setWarning("Searching For Players...");
    }
}

void HostController::handleStopSearch()
{
    auto& host_device = (Host&)NetworkManager::GetDevice();
    host_device.stopListening();

    lobbyForm->getLobby().stopSearch();
    lobbyForm->getPlayerStaging().stopSearching();
    lobbyForm->getSearchButton().setText("Search");
}

void HostController::handleAddAi(Player new_ai)
{
    lobbyForm->getLobby().addPlayer(new_ai);
    lobbyForm->getConsole().setMessage("Welcome, " + new_ai.getName() + "!");

    if (lobbyForm->getLobby().isSearching() && lobbyForm->getLobby().getNumPlayers() >= Lobby::MAX_PLAYERS)
    {
        handleStopSearch();
    }
}

void HostController::putSocket(int sock, int index)
{
    socket_map.insert({sock, index});
}

void HostController::handleKickPlayer(int id)
{
    lobbyForm->kickPlayer(id);
}

void HostController::sendKickMessages(int id)
{
    int sock_to_disconnect = -1;
    for (auto& pair : socket_map)
    {
        if (pair.second == id)
        {
            sock_to_disconnect = pair.first;
            break;
        }
    }

    if (sock_to_disconnect != -1)
    {
        DataMessage* kick_message = new KickPlayer(id);
        kick_message->setSendType(SendType::Both);
        kick_message->setRecipient(sock_to_disconnect);
        kick_message->setRecipientType(RecipientType::Broadcast_Except_Recipient);
        DataManager::PushMessage(kick_message);

        DataMessage* disconnect_msg = new CloseRoom("Kicked From Lobby!", true);
        disconnect_msg->setSendType(SendType::Network);
        disconnect_msg->setRecipient(sock_to_disconnect);
        disconnect_msg->setRecipientType(RecipientType::Single);
        DataManager::PushMessage(disconnect_msg);
    }
    else
    {
        DataMessage* kick_message = new KickPlayer(id);
        kick_message->setSendType(SendType::Both);
        DataManager::PushMessage(kick_message);
    }
}

void HostController::handleDisconnect(int sock)
{
    int playerId = socket_map[sock];
    bool suddenDisconnect = lobbyForm->getLobby().hasId(playerId);
    if (suddenDisconnect)
    {
        selectPlayerToKick(playerId);
        socket_map.erase(sock);
    }
}

void HostController::sendCloseMessages()
{
    DataMessage* close_message = new CloseRoom("Host Has Closed Lobby", true);
    close_message->setSendType(SendType::Both);
    DataManager::PushMessage(close_message);
}

void HostController::handleEnterMatch()
{
    Lobby& lobby = lobbyForm->getLobby();
    lobbyForm->stopChat();
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

    MatchForm* matchForm = new MatchForm(LobbyType::HOST, Match(players, num_players, my_id, my_index));
    matchForm->onClosed([this](void* return_val) {
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

void HostController::handleAddPlayer(Player new_player)
{
    lobbyForm->getLobby().addPlayer(new_player);
    if (!new_player.isDummy()) lobbyForm->getConsole().setMessage("Welcome, " + new_player.getName() + "!");
    if (lobbyForm->getLobby().isSearching() && lobbyForm->getLobby().getNumPlayers() >= Lobby::MAX_PLAYERS)
    {
        handleStopSearch();
    }
}

void HostController::handleRequestJoinLobby(const std::string& name, int sock_fd)
{
    int player_index = socket_map[sock_fd];
    if (dummy_players.find(player_index) != dummy_players.end())
    {
        dummy_players.erase(player_index);
        Lobby& lobby = lobbyForm->getLobby();
        PlayerColor color = lobby.getAvailableColorRGBY();
        Player new_player = lobby.createPlayer(name, color);

        Lobby client_lobby = lobby;
        client_lobby.setMyId(new_player.getId());
        client_lobby.setMyIndex(player_index);

        DataMessage* join_msg = new LobbyUpdate(client_lobby);
        join_msg->setSendType(SendType::Network);
        join_msg->setRecipient(sock_fd);
        join_msg->setRecipientType(RecipientType::Single);
        DataManager::PushMessage(join_msg);

        DataMessage* update_player_msg = new UpdatePlayer(new_player, player_index);
        update_player_msg->setSendType(SendType::Both);
        update_player_msg->setRecipientType(RecipientType::Broadcast);
        DataManager::PushMessage(update_player_msg);
    }
}

void HostController::handleUpdatePlayer(const Player& player, int index)
{
    Lobby& lobby = lobbyForm->getLobby();
    bool was_dummy = lobby.getPlayerByIndex(index).isDummy();

    lobby.setPlayer(player, index);

    if (was_dummy) lobbyForm->getConsole().setMessage("Welcome, " + player.getName() + "!");
}
