//
// Created by Brandon Martin on 4/10/19.
//

#include <Uno/Messages/LobbyUpdate.h>
#include <Demo/TestForm.h>
#include "Uno/Constants.h"
#include "Uno/Network/NetworkManager.h"
#include "Cursen/CursenApplication.h"
#include "Cursen/Events/EventManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "LobbyForm.h"
#include "Uno/GameObjects/LobbyType.h"
#include "Uno/Lobby/LobbyController.h"
#include "Uno/Lobby/HostController.h"
#include "Uno/Lobby/LocalController.h"
#include "Uno/Lobby/ClientController.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Messages/InputKick.h"
#include "Uno/Messages/RequestJoinLobby.h"
#include "Uno/Network/Client.h"

using namespace cursen;

LobbyForm::LobbyForm() :
        Form(Vect2(70, 33)), lobby(nullptr)
{
}

void LobbyForm::initialize()
{
    border.initialize();
    border.setSize(getSize() - Vect2(0, 1));

    start_button.initialize();
    start_button.setPosition(Vect2(1, 16));
    start_button.setLength(34);
    start_button.setText("Start Game");
    start_button.setEnabled(false);
    start_button.onClick([this]() { controller->clickStart(); });

    add_ai_button.initialize();
    add_ai_button.setPosition(Vect2(1, 19));
    add_ai_button.setLength(17);
    add_ai_button.setText("Add AI");
    add_ai_button.setEnabled(false);
    add_ai_button.onClick([this]() { controller->clickAddAI(); });

    search_button.initialize();
    search_button.setPosition(Vect2(18, 19));
    search_button.setLength(17);
    search_button.setText("Search");
    search_button.setEnabled(false);
    search_button.onClick([this]() { controller->clickSearch(); });

    kick_button.initialize();
    kick_button.setPosition(Vect2(1, 22));
    kick_button.setLength(34);
    kick_button.setText("Kick Player");
    kick_button.setEnabled(false);
    kick_button.onClick([this]() { enableRemovePlayerCursor(); });

    close_button.initialize();
    close_button.setPosition(Vect2(1, 25));
    close_button.setLength(34);
    close_button.setText("Close Lobby");
    close_button.setEnabled(false);
    close_button.onClick([this]() { controller->clickClose(); });

    change_color_button.initialize();
    change_color_button.setPosition(Vect2(1, 28));
    change_color_button.setLength(17);
    change_color_button.setText("Change Color");
    change_color_button.setEnabled(false);
    change_color_button.onClick([this]() { controller->clickChangeColor(); });

    chat_button.initialize();
    chat_button.setPosition(Vect2(18, 28));
    chat_button.setLength(17);
    chat_button.setText("Chat");
    chat_button.setEnabled(false);
    chat_button.onClick([this]() { startChat(); });

    console.initialize();

    playerStaging.initialize();
    playerStaging.setCallBacks(this);
    playerStaging.setPosition(Vect2(0, 6));

    art.initialize();
    art.loadFromFile("../test.txt");
    art.setPosition(Vect2(0, 0));
    art.setHidden(true);

    mode_select_box.initialize();
    mode_select_box.setPosition(Vect2(17, 7));
    mode_select_box.onLocalClick([this]() { initializeForLocal(); });
    mode_select_box.onHostClick([this]() { initializeForHost(); });
    mode_select_box.onJoinClick([this]() { mode_select_box.startIpEntry([&](const Event& e) { this->tryJoin(); }); });
    mode_select_box.onExitClick([this]() { closeForm(nullptr); });
    mode_select_box.setLobby(this);

    chat_box.initialize();
    chat_box.setPosition(Vect2(35, 16));
    chat_box.onEscapePress([this](const Event& event) { stopChat(); });
    chat_box.setActive(false);
    chat_box.setEnabled(false);

    lobby_cursor.initialize();
    lobby_cursor.moveTo(&start_button);
    lobby_cursor.mapComponent(&start_button, ArrowMap(nullptr, &change_color_button, nullptr, &add_ai_button));
    lobby_cursor.mapComponent(&add_ai_button,
                              ArrowMap(&search_button, &start_button, &search_button, &kick_button));
    lobby_cursor.mapComponent(&search_button,
                              ArrowMap(&add_ai_button, &start_button, &add_ai_button, &kick_button));
    lobby_cursor.mapComponent(&kick_button, ArrowMap(nullptr, &add_ai_button, nullptr, &close_button));
    lobby_cursor.mapComponent(&close_button, ArrowMap(nullptr, &kick_button, nullptr, &change_color_button));
    lobby_cursor.mapComponent(&change_color_button,
                              ArrowMap(&chat_button, &close_button, &chat_button, &start_button));
    lobby_cursor.mapComponent(&chat_button, ArrowMap(&change_color_button, &close_button, &change_color_button,
                                                             &start_button));
    glowBorder.initialize();
    glowBorder.setDrawOrder(10);
    glowBorder.colorize();

    console.setEnabled(true);

    onUpdate([&]()
    {
        if (lobby != nullptr)
        {
            playerStaging.update(*lobby);
            if (start_button.isEnabled())
            {
                start_button.emphasize();
            }
            else
            {
                start_button.demphasize();
            }
        }
    });

    if (CursenApplication::GetArgc() > 1)
    {
        mode_select_box.getMainPlayerStage().setText(CursenApplication::GetArgv()[1]);
        setMainPlayerName();
    }
    else
    {
        mode_select_box.getMainPlayerStage().activateTextField();
        mode_select_box.getMainPlayerStage().getTextField().onEnterPress(
                [&](const Event& event) { this->setMainPlayerName(); });
    }

    onOpen([this]()
    {
        DataManager::SetContext(Context::ContextLobby);
    });
}

void LobbyForm::updateLobby(Lobby& lobby)
{
    if (this->lobby == nullptr)
    {
        this->lobby = new Lobby(lobby);
        initializeForClient();
    }
    else {
        *this->lobby = lobby;
    }

    chat_box.update(lobby.getMessages());
    playerStaging.update(lobby);
    if (lobby.isSearching())
    {
        startSearch();
    }
    else {
        stopSearch();
    }
}

void LobbyForm::initializeForLocal()
{
    lobby = new Lobby;
    controller = new LocalController(this);
    controller->initialize();

    Player my_player = lobby->createPlayer(mode_select_box.getPlayerName(), PlayerColor::BLUE);
    lobby->setMyId(my_player.getId());
    lobby->addPlayer(my_player);
    lobby->setMyIndex(0);

    console.setMessage("Welcome To Uno!");

    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    chat_box.setEnabled(true);
    start_button.enableIf([&]() { return lobby->getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START; });
    search_button.setEnabled(false);
    add_ai_button.enableIf([&]() { return lobby->getNumPlayers() < Lobby::MAX_PLAYERS; });
    add_ai_button.setEnabled(true);
    kick_button.enableIf([&]() { return lobby->getNumPlayers() > 1; });
    chat_button.setEnabled(false);
    change_color_button.setEnabled(true);
    close_button.setEnabled(true);

    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);
}

void LobbyForm::initializeForHost()
{
    lobby = new Lobby;
    controller = new HostController(this);
    controller->initialize();

    Player host_player = lobby->createPlayer(mode_select_box.getPlayerName(), PlayerColor::BLUE);
    lobby->addPlayer(host_player);
    lobby->setMyId(host_player.getId());
    lobby->setMyIndex(0);

    NetworkManager::SetMode(NetworkMode::Host);

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    chat_box.setEnabled(true);

    start_button.enableIf([&]() { return lobby->getNumPlayers() >= Lobby::MIN_PLAYERS_TO_START; });
    search_button.enableIf([&]() { return lobby->getNumPlayers() < Lobby::MAX_PLAYERS; });
    add_ai_button.enableIf([&]() { return lobby->getNumPlayers() < Lobby::MAX_PLAYERS; });
    add_ai_button.setEnabled(true);
    kick_button.enableIf([&]() { return lobby->getNumPlayers() > 1; });
    chat_button.setEnabled(true);
    change_color_button.setEnabled(true);
    close_button.setEnabled(true);

    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);
}

void LobbyForm::initializeForClient()
{
    controller = new ClientController(this);
    controller->initialize();

    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&close_button);
    lobby_cursor.setEnabled(true);
    chat_box.setEnabled(true);
    close_button.setText("Leave Lobby");

    start_button.setEnabled(false);
    search_button.setEnabled(false);
    add_ai_button.setEnabled(false);
    kick_button.setEnabled(false);
    chat_button.setEnabled(true);
    change_color_button.setEnabled(true);
    close_button.setEnabled(true);
}

void LobbyForm::cleanLobby(std::string exit_message, bool was_kicked)
{
    mode_select_box.setHidden(false);
    lobby_cursor.setEnabled(false);
    chat_box.setEnabled(false);

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

    stopChat();

    console.setMessage("");
    chat_box.clearAllMessages();
    close_button.setText("Close Lobby");

    if (was_kicked)
    {
        mode_select_box.setWarning(exit_message);
    }
    else
    {
        mode_select_box.setMessage(exit_message);
    }

    delete lobby;
    delete controller;
    lobby = nullptr;
    controller = nullptr;

    //glowBorder.setEnabled(true);
}

void LobbyForm::startSearch()
{
    lobby->startSearch();
    playerStaging.startSearching();
    search_button.setText("Stop Search");
    console.setWarning("Searching For Players...");
}

void LobbyForm::stopSearch()
{
    lobby->stopSearch();
    playerStaging.stopSearching();
    search_button.setText("Search");
}

void LobbyForm::tryJoin()
{
    mode_select_box.detachEnterPress();

    std::string address = mode_select_box.getIpAddress();
    if (address == "" || address == "127.0.0.1" || address == "localhost")
    {
        address = "::0";
    };

    NetworkManager::SetMode(NetworkMode::Client);
    auto& device = (Client&) NetworkManager::GetDevice();
    device.initialize();

    if (device.openConnection(address.c_str()))
    {
        mode_select_box.setText("Waiting for Lobby Info...");

        std::string name = mode_select_box.getPlayerName();
        DataMessage* msg = new RequestJoinLobby(name);
        msg->setSendType(SendType::Network);
        DataManager::PushMessage(msg);
    }
    else
    {
        mode_select_box.setWarning("Unable To Join :(");
        mode_select_box.enableCursor();
    }

    mode_select_box.cleanIpEntry();

}

void LobbyForm::enableRemovePlayerCursor()
{
    lobby_cursor.setEnabled(false);
    playerStaging.enableCursor();
    console.setMessage("Select Player to Kick");
}

void LobbyForm::setMainPlayerName()
{
    TextField& field = mode_select_box.getMainPlayerStage().getTextField();
    if (!field.getText().empty())
    {
        std::string name = field.getText();
        mode_select_box.setPlayerName(name);
        mode_select_box.getMainPlayerStage().setPlayer(Player(name, PlayerColor::BLUE, 0, false, false));
        field.setEnabled(false);
        mode_select_box.start();

        glowBorder.setEnabled(true);

    }
    else
    {
        CursesManager::Beep();
        mode_select_box.setWarning("Name Must Have 1 Character");
    }
}

void LobbyForm::selectPlayerToRemove(int playerNum)
{
    lobby_cursor.setEnabled(true);
    playerStaging.disableCursor();
    sendInputRemovePlayer(playerNum);
}

void LobbyForm::sendInputRemovePlayer(int index)
{
    if (index != 0)
    {
        DataMessage* msg = new InputKick(index);
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);
    }
    else
    {
        console.setMessage("Okay, Never mind");
    }
}


void LobbyForm::startChat()
{
    if (!chat_box.isActive())
    {
        chat_box.setActive(true);
        lobby_cursor.setEnabled(false);
        chat_button.setForeground(Color::GREEN);
        console.setMessage("Press Escape to Finish Chatting");
        chat_box.onEnterPress([&](const Event& e) { controller->sendChat(); });
    }
}

void LobbyForm::stopChat()
{
    if (chat_box.isActive())
    {
        chat_box.detachEnterPress();
        chat_box.setActive(false);
        lobby_cursor.setEnabled(true);
        chat_button.setForeground(Color::WHITE);
    }
}

void LobbyForm::changeColor(int playerIndex, PlayerColor color)
{
    lobby->changePlayerColor(playerIndex, color);
    chat_box.update(lobby->getMessages());
}

void LobbyForm::pushChatMessage(int player_index, std::string message)
{
    PlayerColor color = lobby->getPlayerColor(player_index);
    ChatEntry entry(player_index, message, color);
    lobby->pushMessage(entry);
    chat_box.update(lobby->getMessages());
}

void LobbyForm::kickPlayer(int index)
{
    Player p = lobby->getPlayerByIndex(index);
    lobby->removePlayerByIndex(index);
    chat_box.update(lobby->getMessages());
    console.setWarning("Later, " + p.getName());
}

Lobby& LobbyForm::getLobby()
{
    return *this->lobby;
}

void LobbyForm::enterMatch()
{
    controller->handleEnterMatch();
}