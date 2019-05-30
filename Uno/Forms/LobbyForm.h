//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_LOBBYFORM_H
#define CURSEN_LOBBYFORM_H

#include "Cursen/Components/TextField.h"
#include "Cursen/Components/Form.h"
#include "Cursen/Components/Button.h"
#include "Cursen/Components/ASCIIArt.h"
#include "Cursen/Cursor/Cursor.h"
#include "Uno/UnoComponents/LobbyGlowBorder.h"
#include "Uno/UnoComponents/UnoConsole.h"
#include "Uno/UnoComponents/PlayerStaging.h"
#include "Uno/UnoComponents/ModeSelectBox.h"
#include "Uno/GameObjects/Lobby.h"

class Lobby;
class LobbyController;

class LobbyForm : public cursen::Form {

public:

    LobbyForm();
    void initialize() override;
    void cleanLobby();

    void initializeForLocal();
    void initializeForHost();
    void initializeForClient();

    void leaveLocal();
    void leaveHost();
    void leaveClient();

    void updateForLocal();
    void updateForHost();
    void updateForClient();

    void toggleSearch();

    void enableRemovePlayerCursor();

    void selectPlayerToRemove(const int& index);
    void removePlayer(const int& index);

    void setMainPlayerName();

    void clickStart();
    void clickAddAI();
    void clickSearch();
    void clickKick();
    void clickClose();
    void clickSettings();
    void clickLocal();
    void clickHost();
    void clickJoin();
    void clickExit();
    void clickChangeColor();
    void clickChat();

    UnoConsole& getConsole() { return this->console; };
    Lobby& getLobby() { return *this->lobby; };

private:

    // Instance Data
    Lobby* lobby;
    LobbyController* controller;
    Player my_player;

    // Components
    cursen::ASCIIArt art;
    cursen::Box border;
    cursen::Button start_button;
    cursen::Button add_ai_button;
    cursen::Button search_button;
    cursen::Button kick_button;
    cursen::Button close_button;
    cursen::Button change_color_button;
    cursen::Button chat_button;
    cursen::TextField text_field;
    cursen::Cursor lobby_cursor;

    UnoConsole console;
    PlayerStaging playerStaging;
    ModeSelectBox mode_select_box;

    LobbyGlowBorder glowBorder;

};


#endif //CURSEN_LOBBYFORM_H
