//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_LOBBYFORM_H
#define CURSEN_LOBBYFORM_H

#include "Components/Form.h"
#include "Components/Button.h"
#include "Components/ASCIIArt.h"
#include "Cursor/Cursor.h"
#include "../UnoComponents/UnoConsole.h"
#include "../UnoComponents/PlayerStaging.h"

class LobbyForm : public Form {

public:

    LobbyForm();
    void initialize() override;

    void clickStart();
    void clickAddAI();
    void clickSearch();
    void clickKick();
    void clickClose();
    void clickSettings();

private:

    ASCIIArt art;
    Box border;
    Button start_button;
    Button add_ai_button;
    Button search_button;
    Button kick_button;
    Button close_button;
    Button settings_button;
    UnoConsole console;
    PlayerStaging playerStaging;

    Cursor lobby_cursor;

};


#endif //CURSEN_LOBBYFORM_H
