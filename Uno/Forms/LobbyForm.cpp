//
// Created by Brandon Martin on 4/10/19.
//

#include "LobbyForm.h"

LobbyForm::LobbyForm() :
        Form(Size(70,33))
{

}

void LobbyForm::initialize() {

    settings_button.initialize();
    settings_button.setPosition(Size(0,0));
    settings_button.setLength(10);
    add(&settings_button);

}
