//
// Created by Brandon Martin on 5/20/19.
//

#include "HostController.h"

HostController::HostController(LobbyForm* lobbyForm) : LobbyController(lobbyForm)
{}


void HostController::initialize()
{
    lobbyForm->initializeLobby(LobbyType::HOST);
}

void HostController::destroy()
{

}

void HostController::clickStart()
{
    // Broadcast message to start the game
    lobbyForm->getConsole().setText("Start Clicked!");
}

void HostController::clickAddAI()
{
    Lobby& lobby = lobbyForm->getLobby();
    UnoConsole& console = lobbyForm->getConsole();

    console.setText("Add AI Clicked!");
    Player *p = new Player(Player::GetComputerName(), lobbyForm->getLobby().getAvailableColorRGBY());
    lobby.addPlayer(p);
    console.setMessage("Welcome, " + p->getName() + "!");
    lobbyForm->updateLobby();
    // Broadcast message to add an AI
}

void HostController::clickSearch()
{
    // Broadcast message to twirl
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Search Clicked!");
    lobbyForm->toggleSearch();
}

void HostController::clickKick()
{
    // First select player
    // then broadcast message
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Kick Clicked!");
    lobbyForm->enableRemovePlayerCursor();
}

void HostController::clickClose()
{
    // Broadcast close
    lobbyForm->leaveLobby();
}

void HostController::clickChangeColor()
{
    // Broadcast color change
    Lobby& lobby = lobbyForm->getLobby();
    lobby.getPlayer(0)->setColor(lobby.getAvailableColor());
    lobbyForm->updateLobby();
}

void HostController::clickChat()
{

}

