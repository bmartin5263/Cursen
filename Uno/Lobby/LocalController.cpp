//
// Created by Brandon Martin on 5/20/19.
//

#include <Uno/Messages/InputEnterMatch.h>
#include <Uno/Match/MatchReturnData.h>
#include <Uno/Network/NetworkManager.h>
#include "LocalController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Messages/InputAddAi.h"
#include "Uno/Messages/InputKick.h"
#include "Uno/Messages/InputCloseRoom.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Forms/MatchForm.h"
#include "Uno/GameObjects/Match.h"

LocalController::LocalController(LobbyForm* form) : LobbyController(form)
{

}

void LocalController::initialize()
{
    NetworkManager::SetMode(NetworkMode::Local);
}


void LocalController::clickStart()
{
    DataMessage* msg = new InputEnterMatch(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::clickAddAI()
{
    DataMessage* msg = new InputAddAi;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::clickSearch()
{
    assert(false);
}

void LocalController::clickClose()
{
    DataMessage* msg = new InputCloseRoom(lobbyForm->getLobby().getMyId());
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void LocalController::sendChat()
{
    assert(false);
}

void LocalController::handleClose(std::string msg, bool kicked)
{
    NetworkManager::Destroy();
    lobbyForm->cleanLobby("Welcome to Uno!", false);
}

void LocalController::handleStartSearch()
{
    assert(false);
}

void LocalController::handleStopSearch()
{
    assert(false);
}

void LocalController::handleKickPlayer(int index)
{
    Lobby& lobby = lobbyForm->getLobby();
    Player p = lobby.getPlayer(index);
    lobby.removePlayer(index);
    lobbyForm->removePlayerFromStaging(index);
    lobbyForm->getChatBox().update(lobby.getMessages());
    lobbyForm->getConsole().setWarning("Later, " + p.getName());
}

void LocalController::handleInputKick(int index)
{
    int numPlayers = lobbyForm->getLobby().getNumPlayers();
    if (index > 0 && index < numPlayers)
    {
        DataMessage* msg = new KickPlayer(index);
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);
    }
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

void LocalController::handleEnterMatch()
{
    Lobby& lobby = lobbyForm->getLobby();
    lobbyForm->stopChat();
    Player* players = lobby.getPlayers();
    int num_players = lobby.getNumPlayers();
    int my_id = lobby.getMyId();
    int my_index = -1;
    for (int i = 0; i < num_players; ++i)
        if (players[i].getId() == my_id) my_index = i;

    MatchForm* matchForm = new MatchForm(LobbyType::LOCAL, Match(players, num_players, my_id, my_index));
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
            for (int i = 0; i < lobbyForm->getLobby().getNumPlayers(); ++i) lobbyForm->getLobby().getPlayer(i) = returnData->players[i];
        }
        delete returnData;
    });
    lobbyForm->openForm(matchForm);
}

void LocalController::handleAddPlayer(Player new_player)
{
    lobbyForm->getLobby().addPlayer(new_player);
    lobbyForm->addPlayerToStaging(new_player);
    if (!new_player.isDummy()) lobbyForm->getConsole().setMessage("Welcome, " + new_player.getName() + "!");
}

void LocalController::handleRequestJoinLobby(const std::string& name, int sock_fd)
{
    assert(false);
}

void LocalController::handleUpdatePlayer(const Player& player, int index)
{
    Lobby& lobby = lobbyForm->getLobby();
    bool was_dummy = lobby.getPlayer(index).isDummy();

    lobby.setPlayer(player, index);
    lobbyForm->setPlayerToStaging(player, index);

    if (was_dummy) lobbyForm->getConsole().setMessage("Welcome, " + player.getName() + "!");
}

void LocalController::handleInputColorChange(int sender)
{
    UNUSED_VAR(sender)

    PlayerColor new_color = lobbyForm->getLobby().getAvailableColor();
    DataMessage* msg = new ChangeColor(0, new_color);
    msg->setSendType(SendType::Both);
    DataManager::PushMessage(msg);
}

void LocalController::handleChatInput(int sender, const std::string& message)
{
    UNUSED_VAR(sender);
    UNUSED_VAR(message);
    assert(false);
}
