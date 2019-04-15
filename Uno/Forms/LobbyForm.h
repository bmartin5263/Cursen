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

class LobbyForm : public Form {

public:

    LobbyForm();
    void initialize() override;

    void initializeLobby(LobbyType lobbyType);
    void leaveLobby();

    void updateLobby();
    void toggleSearch();

    void enableRemovePlayerCursor();
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

private:

    // Instance Data
    Lobby* lobby;

    // Components
    ASCIIArt art;
    Box border;
    Button start_button;
    Button add_ai_button;
    Button search_button;
    Button kick_button;
    Button close_button;
    Button settings_button;
    TextField text_field;
    UnoConsole console;
    PlayerStaging playerStaging;
    ModeSelectBox mode_select_box;
    Cursor lobby_cursor;

};


#endif //CURSEN_LOBBYFORM_H
