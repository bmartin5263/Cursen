//
// Created by Brandon Martin on 5/20/19.
//

#include "ClientController.h"

ClientController::ClientController(LobbyForm* form) : LobbyController(form)
{

}

void ClientController::initialize()
{
    lobbyForm->initializeForClient();
}

void ClientController::destroy()
{
    lobbyForm->leaveClient();
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

void ClientController::clickKick()
{
    throw std::logic_error("Client cannot kick.");
}

void ClientController::clickClose()
{
    destroy();
}

void ClientController::clickChangeColor()
{
    Lobby& lobby = lobbyForm->getLobby();
    lobby.getPlayer(0)->setColor(lobby.getAvailableColor());
    update();
}

void ClientController::clickChat()
{
    lobbyForm->startChat();
}

void ClientController::update()
{
    lobbyForm->updateForClient();
}
