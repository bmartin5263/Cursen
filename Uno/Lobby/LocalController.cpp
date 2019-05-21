//
// Created by Brandon Martin on 5/20/19.
//

#include "LocalController.h"

LocalController::LocalController(LobbyForm* form) : LobbyController(form)
{

}

void LocalController::initialize()
{
    lobbyForm->initializeForLocal();
}

void LocalController::destroy()
{

}

void LocalController::clickStart()
{
    lobbyForm->getConsole().setText("Start Clicked!");
}

void LocalController::clickAddAI()
{
    Lobby& lobby = lobbyForm->getLobby();
    UnoConsole& console = lobbyForm->getConsole();

    console.setText("Add AI Clicked!");
    Player *p = new Player(Player::GetComputerName(), lobbyForm->getLobby().getAvailableColorRGBY());
    lobby.addPlayer(p);
    console.setMessage("Welcome, " + p->getName() + "!");
    update();
}

void LocalController::clickSearch()
{
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Search Clicked!");
    lobbyForm->toggleSearch();
}

void LocalController::clickKick()
{
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Kick Clicked!");
    lobbyForm->enableRemovePlayerCursor();
}

void LocalController::clickClose()
{
    lobbyForm->leaveLobby();
}

void LocalController::clickChangeColor()
{
    Lobby& lobby = lobbyForm->getLobby();
    lobby.getPlayer(0)->setColor(lobby.getAvailableColor());
    update();
}

void LocalController::clickChat()
{

}

void LocalController::update()
{
    lobbyForm->updateForLocal();
}
