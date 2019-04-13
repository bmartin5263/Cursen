//
// Created by Brandon Martin on 4/10/19.
//

#include "LobbyForm.h"
#include "Drawing/CursesManager.h"
#include "../GameObjects/LobbyType.h"

LobbyForm::LobbyForm() :
        Form(Size(70,33)), lobby(nullptr)
{

}

void LobbyForm::initialize() {

    border.initialize();
    border.setSize(getSize() - Size(0,1));

    start_button.initialize();
    start_button.setPosition(Size(1,16));
    start_button.setLength(34);
    start_button.setText("Start Game");
    start_button.setEnabled(false);
    start_button.onClick(std::bind(&LobbyForm::clickStart, this));

    add_ai_button.initialize();
    add_ai_button.setPosition(Size(1,19));
    add_ai_button.setLength(17);
    add_ai_button.setText("Add AI");
    add_ai_button.setEnabled(false);
    add_ai_button.onClick(std::bind(&LobbyForm::clickAddAI, this));

    search_button.initialize();
    search_button.setPosition(Size(18,19));
    search_button.setLength(17);
    search_button.setText("Search");
    search_button.setEnabled(false);
    search_button.onClick(std::bind(&LobbyForm::clickSearch, this));

    kick_button.initialize();
    kick_button.setPosition(Size(1,22));
    kick_button.setLength(34);
    kick_button.setText("Kick Player");
    kick_button.setEnabled(false);
    kick_button.onClick(std::bind(&LobbyForm::clickKick, this));

    close_button.initialize();
    close_button.setPosition(Size(1,25));
    close_button.setLength(34);
    close_button.setText("Close Room");
    close_button.setEnabled(false);
    close_button.onClick(std::bind(&LobbyForm::clickClose, this));

    settings_button.initialize();
    settings_button.setPosition(Size(1,28));
    settings_button.setLength(34);
    settings_button.setText("Settings");
    settings_button.setEnabled(false);
    settings_button.onClick(std::bind(&LobbyForm::clickSettings, this));

    console.initialize();

    playerStaging.initialize();
    playerStaging.setPosition(Size(0,6));

    art.initialize();
    art.loadFromFile("../test.txt");
    art.setPosition(Size(0,0));
    art.setHidden(true);

    mode_select_box.initialize();
    mode_select_box.setPosition(Size(17, 7));
    mode_select_box.onLocalClick(std::bind(&LobbyForm::clickLocal, this));
    mode_select_box.onHostClick(std::bind(&LobbyForm::clickHost, this));
    mode_select_box.onJoinClick(std::bind(&LobbyForm::clickJoin, this));
    mode_select_box.onExitClick(std::bind(&LobbyForm::clickExit, this));

    lobby_cursor.moveTo(&start_button);
    lobby_cursor.mapComponent(&start_button, ArrowMap(nullptr, &settings_button, nullptr, &add_ai_button));
    lobby_cursor.mapComponent(&add_ai_button, ArrowMap(&search_button, &start_button, &search_button, &kick_button));
    lobby_cursor.mapComponent(&search_button, ArrowMap(&add_ai_button, &start_button, &add_ai_button, &kick_button));
    lobby_cursor.mapComponent(&kick_button, ArrowMap(nullptr, &add_ai_button, nullptr, &close_button));
    lobby_cursor.mapComponent(&close_button, ArrowMap(nullptr, &kick_button, nullptr, &settings_button));
    lobby_cursor.mapComponent(&settings_button, ArrowMap(nullptr, &close_button, nullptr, &start_button));
    //lobby_cursor.setEnabled(false);

}

void LobbyForm::clickStart() {
    console.setText("Start Clicked!");
}

void LobbyForm::clickAddAI() {
    console.setText("Add AI Clicked!");
}

void LobbyForm::clickSearch() {
    console.setText("Search Clicked!");
    playerStaging.toggleSearch();
}

void LobbyForm::clickKick() {
    console.setText("Kick Clicked!");
}

void LobbyForm::clickClose() {
    leaveLobby();
}

void LobbyForm::clickSettings() {
    console.setText("Settings Clicked!");
}

void LobbyForm::clickLocal() {
    enterLobby(LobbyType::LOCAL);
}

void LobbyForm::clickHost() {
    enterLobby(LobbyType::HOST);
}

void LobbyForm::clickJoin() {
    enterLobby(LobbyType::JOIN);
}

void LobbyForm::clickExit() {
    CursenApplication::Quit();
}

void LobbyForm::enterLobby(LobbyType type) {
    lobby = new Lobby(type);
    mode_select_box.setHidden(true);

    switch(type) {
        case LobbyType::LOCAL:
            add_ai_button.setEnabled(true);
            start_button.setEnabled(false);
            search_button.setEnabled(false);
            close_button.setEnabled(true);
            settings_button.setEnabled(true);
            kick_button.setEnabled(true);
            lobby_cursor.moveTo(&add_ai_button);
            break;
        case LobbyType::HOST:
            add_ai_button.setEnabled(true);
            start_button.setEnabled(false);
            search_button.setEnabled(true);
            close_button.setEnabled(true);
            settings_button.setEnabled(true);
            kick_button.setEnabled(true);
            lobby_cursor.moveTo(&add_ai_button);
            break;
        case LobbyType::JOIN:
            add_ai_button.setEnabled(false);
            start_button.setEnabled(false);
            search_button.setEnabled(false);
            close_button.setEnabled(true);
            settings_button.setEnabled(false);
            kick_button.setEnabled(false);
            lobby_cursor.moveTo(&close_button);
            break;
    }

    lobby_cursor.setEnabled(true);
}

void LobbyForm::leaveLobby() {
    mode_select_box.setHidden(false);
    lobby_cursor.setEnabled(false);

    add_ai_button.setEnabled(false);
    start_button.setEnabled(false);
    search_button.setEnabled(false);
    close_button.setEnabled(false);
    settings_button.setEnabled(false);
    kick_button.setEnabled(false);
    playerStaging.stopSearching();

    delete lobby;
}

void LobbyForm::updateLobby() {
    add_ai_button.setEnabled(false);
    start_button.setEnabled(false);
    search_button.setEnabled(false);
    close_button.setEnabled(false);
    settings_button.setEnabled(false);
    kick_button.setEnabled(false);

}
