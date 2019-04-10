//
// Created by Brandon Martin on 4/10/19.
//

#ifndef CURSEN_LOBBYFORM_H
#define CURSEN_LOBBYFORM_H

#include "Components/Form.h"
#include "Components/Button.h"

class LobbyForm : public Form {

public:

    LobbyForm();
    void initialize() override;

private:

    Button start_button;
    Button add_ai_button;
    Button search_button;
    Button kick_button;
    Button close_button;
    Button settings_button;

};


#endif //CURSEN_LOBBYFORM_H
