//
// Created by Brandon Martin on 4/10/19.
//

#include "Cursen/Events/EventManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "LobbyForm.h"
#include "Uno/GameObjects/LobbyType.h"
#include "Uno/Lobby/LobbyController.h"
#include "Uno/Lobby/HostController.h"
#include "Uno/Lobby/LocalController.h"
#include "Uno/Lobby/ClientController.h"

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
    start_button.emphasize();

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
    chat_button.setHighlight(cursen::ColorPair(cursen::Color::VIOLET));
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

    if (cursen::CursenApplication::GetArgc() > 1) {
        mode_select_box.getMainPlayerStage().setText(cursen::CursenApplication::GetArgv()[1]);
        setMainPlayerName();
    }
    else {
        mode_select_box.getMainPlayerStage().activateTextField();
        mode_select_box.getMainPlayerStage().getTextField().onEnterPress(std::bind(&LobbyForm::setMainPlayerName, this));
    }

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
    glowBorder.initialize();
    glowBorder.setDrawOrder(10);
    glowBorder.setEnabled(true);
    glowBorder.colorize();

    onUpdate([&]() {
        if (lobby != nullptr) {
            playerStaging.update(*lobby);
        }
    });
}

void LobbyForm::initializeForLocal()
{
    lobby = new Lobby;

    Player* p = new Player(mode_select_box.getMainPlayerStage().getText(), PlayerColor::BLUE);
    my_player = *p;

    lobby->addPlayer(p);
    updateForLocal();

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);

    start_button.enableIf([&]() {
        return lobby->getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START;
    });

    search_button.enableIf([&]() {
        return false;
    });

    add_ai_button.enableIf([&]() {
        return lobby->getNumPlayers() < Lobby::MAX_PLAYERS;
    });

    kick_button.enableIf([&]() {
        return lobby->getNumPlayers() > 1;
    });

    chat_button.enableIf([&]() {
        return false;
    });

    change_color_button.enableIf([&]() {
        return true;
    });

    close_button.enableIf([&]() {
        return true;
    });

}

void LobbyForm::initializeForHost()
{
    lobby = new Lobby;

    Player* p = new Player(mode_select_box.getMainPlayerStage().getText(), PlayerColor::BLUE);
    my_player = *p;

    lobby->addPlayer(p);
    updateForHost();

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);

    start_button.enableIf([&]() {
        return lobby->getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START;
    });

    search_button.enableIf([&]() {
        return lobby->getNumPlayers() < Lobby::MAX_PLAYERS;
    });

    add_ai_button.enableIf([&]() {
        return lobby->getNumPlayers() < Lobby::MAX_PLAYERS;
    });

    kick_button.enableIf([&]() {
        return lobby->getNumPlayers() > 1;
    });

    chat_button.enableIf([&]() {
        return true;
    });

    change_color_button.enableIf([&]() {
        return true;
    });

    close_button.enableIf([&]() {
        return true;
    });
}

void LobbyForm::initializeForClient()
{
    lobby = new Lobby;

    Player* p = new Player(mode_select_box.getMainPlayerStage().getText(), PlayerColor::BLUE);
    my_player = *p;

    lobby->addPlayer(p);
    updateForClient();

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&close_button);
    lobby_cursor.setEnabled(true);

    start_button.enableIf([&]() {
        return false;
    });

    search_button.enableIf([&]() {
        return false;
    });

    add_ai_button.enableIf([&]() {
        return false;
    });

    kick_button.enableIf([&]() {
        return false;
    });

    chat_button.enableIf([&]() {
        return true;
    });

    change_color_button.enableIf([&]() {
        return true;
    });

    close_button.enableIf([&]() {
        return true;
    });
}

void LobbyForm::cleanLobby()
{
    mode_select_box.setHidden(false);
    lobby_cursor.setEnabled(false);

    add_ai_button.setEnabled(false);
    start_button.setEnabled(false);
    search_button.setEnabled(false);
    close_button.setEnabled(false);
    kick_button.setEnabled(false);
    change_color_button.setEnabled(false);
    chat_button.setEnabled(false);

    add_ai_button.detachEnableIf();
    start_button.detachEnableIf();
    search_button.detachEnableIf();
    close_button.detachEnableIf();
    kick_button.detachEnableIf();
    change_color_button.detachEnableIf();
    chat_button.detachEnableIf();

    playerStaging.stopSearching();
    playerStaging.clear();

    console.setMessage("");

    delete lobby;
    delete controller;
    lobby = nullptr;
    controller = nullptr;

    glowBorder.setEnabled(true);
}

void LobbyForm::leaveLocal()
{
    cleanLobby();
}

void LobbyForm::leaveHost()
{
    cleanLobby();
}

void LobbyForm::leaveClient()
{
    cleanLobby();
}


void LobbyForm::clickStart()
{
    controller->clickStart();
}

void LobbyForm::clickAddAI()
{
    controller->clickAddAI();
}

void LobbyForm::clickSearch()
{
    controller->clickSearch();
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
    controller->update();
}

void LobbyForm::clickKick()
{
    controller->clickKick();
}

void LobbyForm::clickClose()
{
    controller->clickClose();
}

void LobbyForm::clickSettings()
{
    console.setText("Settings Clicked!");
}

void LobbyForm::clickLocal()
{
    controller = new LocalController(this);
    controller->initialize();
}

void LobbyForm::clickHost()
{
    controller = new HostController(this);
    controller->initialize();
}

void LobbyForm::clickJoin()
{
    controller = new ClientController(this);
    controller->initialize();
}

void LobbyForm::clickExit()
{
    cursen::CursenApplication::Quit();
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
    controller->update();
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
    controller->clickChat();
}

void LobbyForm::clickChangeColor()
{
    controller->clickChangeColor();
}

void LobbyForm::selectPlayerToRemove(const int& playerNum)
{
    removePlayer(playerNum);
    lobby_cursor.setEnabled(true);
    playerStaging.disableCursor();
}

void LobbyForm::updateForLocal()
{
    //playerStaging.update(*lobby);
}

void LobbyForm::updateForHost()
{
    //playerStaging.update(*lobby);
}

void LobbyForm::updateForClient()
{
    //playerStaging.update(*lobby);
}