//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_LOBBYFORM_H
#define CURSEN_LOBBYFORM_H

#include <Components/TextField.h>
#include "Components/Form.h"
#include "Components/Button.h"
#include "Components/ASCIIArt.h"
#include "Cursor/Cursor.h"
#include "../UnoComponents/UnoConsole.h"
#include "../UnoComponents/PlayerStaging.h"
#include "../UnoComponents/ModeSelectBox.h"
#include "../GameObjects/Lobby.h"

class Lobby;

class LobbyForm : public cursen::Form {

public:

    LobbyForm();
    void initialize() override;

    void initializeLobby(LobbyType lobbyType);
    void leaveLobby();

    void updateLobby();
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

private:

    // Instance Data
    Lobby* lobby;

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

};


#endif //CURSEN_LOBBYFORM_H
