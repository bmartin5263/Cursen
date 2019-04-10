//
// Created by Brandon Martin on 4/10/19.
//

#include "LobbyForm.h"
#include "Drawing/CursesManager.h"

LobbyForm::LobbyForm() :
        Form(Size(70,33))
{

}

void LobbyForm::initialize() {

    start_button.initialize();
    start_button.setPosition(Size(1,16));
    start_button.setLength(34);
    start_button.setText("Start Game");
    start_button.onClick(std::bind(&LobbyForm::clickStart, this));
    add(&start_button);

    add_ai_button.initialize();
    add_ai_button.setPosition(Size(1,19));
    add_ai_button.setLength(17);
    add_ai_button.setText("Add AI");
    add_ai_button.onClick(std::bind(&LobbyForm::clickAddAI, this));
    add(&add_ai_button);

    search_button.initialize();
    search_button.setPosition(Size(18,19));
    search_button.setLength(17);
    search_button.setText("Search");
    search_button.onClick(std::bind(&LobbyForm::clickSearch, this));
    add(&search_button);

    kick_button.initialize();
    kick_button.setPosition(Size(1,22));
    kick_button.setLength(34);
    kick_button.setText("Kick Player");
    kick_button.onClick(std::bind(&LobbyForm::clickKick, this));
    add(&kick_button);

    close_button.initialize();
    close_button.setPosition(Size(1,25));
    close_button.setLength(34);
    close_button.setText("Close Room");
    close_button.onClick(std::bind(&LobbyForm::clickClose, this));
    add(&close_button);

    settings_button.initialize();
    settings_button.setPosition(Size(1,28));
    settings_button.setLength(34);
    settings_button.setText("Settings");
    settings_button.onClick(std::bind(&LobbyForm::clickSettings, this));
    add(&settings_button);

    console.initialize();
    add(&console);

    art.initialize();
    art.loadFromFile("../test.txt");
    art.setPosition(Size(0,0));
    add(&art);
    art.setHidden(true);

    lobby_cursor.setStart(&start_button);
    lobby_cursor.mapComponent(&start_button, ArrowMap(nullptr, &settings_button, nullptr, &add_ai_button));
    lobby_cursor.mapComponent(&add_ai_button, ArrowMap(&search_button, &start_button, &search_button, &kick_button));
    lobby_cursor.mapComponent(&search_button, ArrowMap(&add_ai_button, &start_button, &add_ai_button, &kick_button));
    lobby_cursor.mapComponent(&kick_button, ArrowMap(nullptr, &add_ai_button, nullptr, &close_button));
    lobby_cursor.mapComponent(&close_button, ArrowMap(nullptr, &kick_button, nullptr, &settings_button));
    lobby_cursor.mapComponent(&settings_button, ArrowMap(nullptr, &close_button, nullptr, &start_button));
    lobby_cursor.setEnabled(true);

}

void LobbyForm::clickStart() {
    console.setText("Start Clicked!");
}

void LobbyForm::clickAddAI() {
    console.setText("Add AI Clicked!");
}

void LobbyForm::clickSearch() {
    console.setText("Search Clicked!");
}

void LobbyForm::clickKick() {
    console.setText("Kick Clicked!");
}

void LobbyForm::clickClose() {
    console.setText("Close Clicked!");
}

void LobbyForm::clickSettings() {
    console.setText("Settings Clicked!");
}
