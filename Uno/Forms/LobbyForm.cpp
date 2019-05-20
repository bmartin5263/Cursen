//
// Created by Brandon Martin on 4/10/19.
//

#include <Events/EventManager.h>
#include "LobbyForm.h"
#include "Drawing/CursesManager.h"
#include "../GameObjects/LobbyType.h"

LobbyForm::LobbyForm() :
        Form(cursen::Vect2(70, 33)), lobby(nullptr)
{

}

void LobbyForm::initialize()
{

    border.initialize();
    border.setSize(getSize() - cursen::Vect2(0, 1));

    start_button.initialize();
    start_button.setPosition(cursen::Vect2(1, 16));
    start_button.setLength(34);
    start_button.setText("Start Game");
    start_button.setEnabled(false);
    start_button.onClick(std::bind(&LobbyForm::clickStart, this));

    add_ai_button.initialize();
    add_ai_button.setPosition(cursen::Vect2(1, 19));
    add_ai_button.setLength(17);
    add_ai_button.setText("Add AI");
    add_ai_button.setEnabled(false);
    add_ai_button.onClick(std::bind(&LobbyForm::clickAddAI, this));

    search_button.initialize();
    search_button.setPosition(cursen::Vect2(18, 19));
    search_button.setLength(17);
    search_button.setText("Search");
    search_button.setEnabled(false);
    search_button.onClick(std::bind(&LobbyForm::clickSearch, this));

    kick_button.initialize();
    kick_button.setPosition(cursen::Vect2(1, 22));
    kick_button.setLength(34);
    kick_button.setText("Kick Player");
    kick_button.setEnabled(false);
    kick_button.onClick(std::bind(&LobbyForm::clickKick, this));

    close_button.initialize();
    close_button.setPosition(cursen::Vect2(1, 25));
    close_button.setLength(34);
    close_button.setText("Close Room");
    close_button.setEnabled(false);
    close_button.onClick(std::bind(&LobbyForm::clickClose, this));

    //settings_button.initialize();
    //settings_button.setPosition(cursen::Vect2(1,28));
    //settings_button.setLength(34);
    //settings_button.setText("Settings");
    //settings_button.setEnabled(false);
    //settings_button.onClick(std::bind(&LobbyForm::clickSettings, this));

    change_color_button.initialize();
    change_color_button.setPosition(cursen::Vect2(1, 28));
    change_color_button.setLength(17);
    change_color_button.setText("Change Color");
    change_color_button.setEnabled(false);
    change_color_button.onClick(std::bind(&LobbyForm::clickChangeColor, this));

    chat_button.initialize();
    chat_button.setPosition(cursen::Vect2(18, 28));
    chat_button.setLength(17);
    chat_button.setText("Chat");
    chat_button.setEnabled(false);

    console.initialize();

    playerStaging.initialize();
    playerStaging.setCallBacks(this);
    playerStaging.setPosition(cursen::Vect2(0, 6));

    art.initialize();
    art.loadFromFile("../test.txt");
    art.setPosition(cursen::Vect2(0, 0));
    art.setHidden(true);

    mode_select_box.initialize();
    mode_select_box.setPosition(cursen::Vect2(17, 7));
    mode_select_box.onLocalClick(std::bind(&LobbyForm::clickLocal, this));
    mode_select_box.onHostClick(std::bind(&LobbyForm::clickHost, this));
    mode_select_box.onJoinClick(std::bind(&LobbyForm::clickJoin, this));
    mode_select_box.onExitClick(std::bind(&LobbyForm::clickExit, this));
    mode_select_box.getMainPlayerStage().activateTextField();
    mode_select_box.getMainPlayerStage().getTextField().onEnterPress(std::bind(&LobbyForm::setMainPlayerName, this));

    lobby_cursor.moveTo(&start_button);
    lobby_cursor.mapComponent(&start_button, cursen::ArrowMap(nullptr, &change_color_button, nullptr, &add_ai_button));
    lobby_cursor.mapComponent(&add_ai_button,
                              cursen::ArrowMap(&search_button, &start_button, &search_button, &kick_button));
    lobby_cursor.mapComponent(&search_button,
                              cursen::ArrowMap(&add_ai_button, &start_button, &add_ai_button, &kick_button));
    lobby_cursor.mapComponent(&kick_button, cursen::ArrowMap(nullptr, &add_ai_button, nullptr, &close_button));
    lobby_cursor.mapComponent(&close_button, cursen::ArrowMap(nullptr, &kick_button, nullptr, &change_color_button));
    lobby_cursor.mapComponent(&change_color_button,
                              cursen::ArrowMap(&chat_button, &close_button, &chat_button, &start_button));
    lobby_cursor.mapComponent(&chat_button, cursen::ArrowMap(&change_color_button, &close_button, &change_color_button,
                                                             &start_button));

    //lobby_cursor.setEnabled(false);
}

void LobbyForm::clickStart()
{
    console.setText("Start Clicked!");
}

void LobbyForm::clickAddAI()
{
    console.setText("Add AI Clicked!");
    Player *p = new Player(Player::GetComputerName(), lobby->getAvailableColorRGBY());
    lobby->addPlayer(p);
    console.setMessage("Welcome, " + p->getName() + "!");
    updateLobby();
}

void LobbyForm::clickSearch()
{
    console.setText("Search Clicked!");
    toggleSearch();
}

void LobbyForm::toggleSearch()
{
    if (!lobby->isSearching()) {
        lobby->startSearch();
        playerStaging.startSearching();
        search_button.setText("Stop Search");
        console.setWarning("Searching For Players...");
    } else {
        lobby->stopSearch();
        playerStaging.stopSearching();
        search_button.setText("Search");
    }
    updateLobby();
}

void LobbyForm::clickKick()
{
    console.setText("Kick Clicked!");
    enableRemovePlayerCursor();
}

void LobbyForm::clickClose()
{
    leaveLobby();
}

void LobbyForm::clickSettings()
{
    console.setText("Settings Clicked!");
}

void LobbyForm::clickLocal()
{
    initializeLobby(LobbyType::LOCAL);
}

void LobbyForm::clickHost()
{
    initializeLobby(LobbyType::HOST);
}

void LobbyForm::clickJoin()
{
    initializeLobby(LobbyType::JOIN);
}

void LobbyForm::clickExit()
{
    cursen::CursenApplication::Quit();
}

void LobbyForm::initializeLobby(LobbyType type)
{
    lobby = new Lobby(type);

    lobby->addPlayer(new Player(mode_select_box.getMainPlayerStage().getText(), PlayerColor::BLUE));
    mode_select_box.setHidden(true);

    updateLobby();

    switch (type) {
        case LobbyType::LOCAL:
            lobby_cursor.moveTo(&add_ai_button);
            break;
        case LobbyType::HOST:
            lobby_cursor.moveTo(&add_ai_button);
            break;
        case LobbyType::JOIN:
            lobby_cursor.moveTo(&close_button);
            break;
    }

    console.setMessage("Welcome To Uno!");

    lobby_cursor.setEnabled(true);
}

void LobbyForm::leaveLobby()
{
    mode_select_box.setHidden(false);
    lobby_cursor.setEnabled(false);

    add_ai_button.setEnabled(false);
    start_button.setEnabled(false);
    search_button.setEnabled(false);
    close_button.setEnabled(false);
    //settings_button.setEnabled(false);
    kick_button.setEnabled(false);
    change_color_button.setEnabled(false);
    chat_button.setEnabled(false);

    playerStaging.stopSearching();
    playerStaging.clear();

    console.setMessage("");

    delete lobby;
    lobby = nullptr;
}

void LobbyForm::updateLobby()
{
    add_ai_button.setEnabled(false);
    start_button.setEnabled(false);
    search_button.setEnabled(false);
    close_button.setEnabled(false);
    //settings_button.setEnabled(false);
    change_color_button.setEnabled(false);
    chat_button.setEnabled(false);
    kick_button.setEnabled(false);
    if (lobby != nullptr) {
        close_button.setEnabled(true);
        if (lobby->getType() != LobbyType::JOIN) {
            if (!lobby->isSearching()) {
                if (lobby->getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START) {
                    start_button.setEnabled(true);
                    start_button.emphasize();
                }
                if (lobby->getNumPlayers() > 1) {
                    kick_button.setEnabled(true);
                }
            }
            if (lobby->getNumPlayers() < Lobby::MAX_PLAYERS) {
                add_ai_button.setEnabled(true);
                if (lobby->getType() == LobbyType::HOST) {
                    search_button.setEnabled(true);
                }
            }
        }
        change_color_button.setEnabled(true);
        chat_button.setEnabled(true);
    }
    lobby_cursor.refresh();
    playerStaging.update(*lobby);
}

void LobbyForm::enableRemovePlayerCursor()
{
    lobby_cursor.setEnabled(false);
    playerStaging.enableCursor();
    console.setMessage("Select Player to Kick");
}

void LobbyForm::removePlayer(const int &playerNum)
{
    if (playerNum != 0) {
        Player p = *lobby->getPlayer(playerNum);
        lobby->removePlayer(playerNum);
        console.setWarning("Later, " + p.getName());
    } else {
        console.setMessage("OK, Nevermind");
    }
    updateLobby();
}

void LobbyForm::setMainPlayerName()
{
    cursen::TextField &field = mode_select_box.getMainPlayerStage().getTextField();
    if (!field.getText().empty()) {
        mode_select_box.getMainPlayerStage().setPlayer(Player(field.getText(), PlayerColor::BLUE));
        field.setEnabled(false);
        mode_select_box.start();
    } else {
        cursen::CursesManager::Beep();
        mode_select_box.setWarning("Name Must Have 1 Character");
    }
}

void LobbyForm::clickChat()
{

}

void LobbyForm::clickChangeColor()
{
    lobby->getPlayer(0)->setColor(lobby->getAvailableColor());
    updateLobby();
}

void LobbyForm::selectPlayerToRemove(const int& playerNum)
{
    removePlayer(playerNum);
    lobby_cursor.setEnabled(true);
    playerStaging.disableCursor();
}
