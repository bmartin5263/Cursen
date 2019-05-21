//
// Created by Brandon Martin on 5/20/19.
//

#include "ClientController.h"

ClientController::ClientController(LobbyForm* form) : LobbyController(form)
{

}

void ClientController::initialize()
{
    lobbyForm->initializeLobby(LobbyType::JOIN);
}

void ClientController::destroy()
{

}

void ClientController::clickStart()
{
    lobbyForm->getConsole().setText("Start Clicked!");
}

void ClientController::clickAddAI()
{
    Lobby& lobby = lobbyForm->getLobby();
    UnoConsole& console = lobbyForm->getConsole();

    console.setText("Add AI Clicked!");
    Player *p = new Player(Player::GetComputerName(), lobbyForm->getLobby().getAvailableColorRGBY());
    lobby.addPlayer(p);
    console.setMessage("Welcome, " + p->getName() + "!");
    lobbyForm->updateLobby();
}

void ClientController::clickSearch()
{
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Search Clicked!");
    lobbyForm->toggleSearch();
}

void ClientController::clickKick()
{
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Kick Clicked!");
    lobbyForm->enableRemovePlayerCursor();
}

void ClientController::clickClose()
{
    lobbyForm->leaveLobby();
}

void ClientController::clickChangeColor()
{
    Lobby& lobby = lobbyForm->getLobby();
    lobby.getPlayer(0)->setColor(lobby.getAvailableColor());
    lobbyForm->updateLobby();
}

void ClientController::clickChat()
{

}
