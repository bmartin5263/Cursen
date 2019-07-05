//
// Created by Brandon Martin on 4/10/19.
//

#include <Uno/Messages/AddPlayer.h>
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
#include "Uno/Messages/AddAI.h"
#include "Uno/Messages/InputKick.h"
#include "Uno/Messages/RequestJoinLobby.h"
#include "Uno/Network/Client.h"

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
    chat_button.setEnabled(false);
    chat_button.onClick(std::bind(&LobbyForm::clickChat, this));

    console.initialize();
    //console.setWarning("                  Developed By Brandon Martin");

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
    mode_select_box.setLobby(this);

    chat_box.initialize();
    chat_box.setPosition(cursen::Vect2(35, 16));
    chat_box.onEscapePress(std::bind(&LobbyForm::stopChat, this));
    chat_box.setActive(false);
    chat_box.setEnabled(false);

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
    //glowBorder.setEnabled(true);
    glowBorder.colorize();

    onUpdate([&]() {
        if (lobby != nullptr) {
            playerStaging.update(*lobby);
            if (start_button.isEnabled()) {
                start_button.emphasize();
            }
            else
            {
                start_button.demphasize();
            }
        }
    });

    DataManager::SetContext(Context::Lobby);
}

void LobbyForm::initializeForLocal()
{
    lobby = new Lobby;

    Player my_player = lobby->createPlayer(mode_select_box.getPlayerName(), PlayerColor::BLUE);
    lobby->setMyId(my_player.getId());
    lobby->addPlayer(my_player);

    NetworkManager::CreateDevice(NetworkType::Local);

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);
    chat_box.setEnabled(true);

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

    Player host_player = lobby->createPlayer(mode_select_box.getPlayerName(), PlayerColor::BLUE);
    lobby->addPlayer(host_player);
    lobby->setMyId(host_player.getId());

    NetworkManager::CreateDevice(NetworkType::Host);

    console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&add_ai_button);
    lobby_cursor.setEnabled(true);
    chat_box.setEnabled(true);

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

    controller = new ClientController(this);

    //console.setMessage("Welcome To Uno!");
    mode_select_box.setHidden(true);
    glowBorder.setEnabled(false);
    lobby_cursor.moveTo(&close_button);
    lobby_cursor.setEnabled(true);
    chat_box.setEnabled(true);

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

    console.setMessage("");
    chat_box.clearAllMessages();

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

void LobbyForm::leaveLocal()
{
    NetworkManager::DestroyDevice();
    cleanLobby("Welcome to Uno!", false);
}

void LobbyForm::leaveHost()
{
    NetworkManager::DestroyDevice();
    NetworkManager::CreateDevice(NetworkType::Local);
    cleanLobby("Welcome to Uno!", false);
}

void LobbyForm::leaveClient(std::string msg, bool kicked)
{
    NetworkManager::DestroyDevice();
    NetworkManager::CreateDevice(NetworkType::Local);
    cleanLobby(msg, kicked);
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


void LobbyForm::clickKick()
{
    enableRemovePlayerCursor();
}

void LobbyForm::clickClose()
{
    controller->clickClose();
}

void LobbyForm::clickSettings()
{
    console.setMessage("Settings Clicked!");
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
    mode_select_box.startIpEntry(std::bind(&LobbyForm::tryJoin, this));
}

void LobbyForm::tryJoin()
{
    mode_select_box.detachEnterPress();

    std::string address = mode_select_box.getIpAddress();
    if (address == "" || address == "127.0.0.1") address = "::0";

    NetworkManager::CreateDevice(NetworkType::Client);
    auto& device = (Client&)NetworkManager::GetDevice();
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

void LobbyForm::clickExit()
{
    cursen::CursenApplication::CloseForm();
}

void LobbyForm::enableRemovePlayerCursor()
{
    lobby_cursor.setEnabled(false);
    playerStaging.enableCursor();
    console.setMessage("Select Player to Kick");
}

void LobbyForm::removePlayer(const int playerNum)
{
    if (playerNum != 0) {
        Player p = lobby->getPlayer(playerNum);
        lobby->removePlayer(playerNum);
        console.setWarning("Later, " + p.getName());
    } else {
        console.setMessage("OK, Nevermind");
    }
}

void LobbyForm::setMainPlayerName()
{
    cursen::TextField &field = mode_select_box.getMainPlayerStage().getTextField();
    if (!field.getText().empty()) {
        std::string name = field.getText();
        mode_select_box.setPlayerName(name);
        mode_select_box.getMainPlayerStage().setPlayer(Player(name, PlayerColor::BLUE, 0));
        field.setEnabled(false);
        mode_select_box.start();

        glowBorder.setEnabled(true);

    } else {
        cursen::CursesManager::Beep();
        mode_select_box.setWarning("Name Must Have 1 Character");
    }
}

void LobbyForm::clickChat()
{
    startChat();
}

void LobbyForm::clickChangeColor()
{
    controller->clickChangeColor();
}

void LobbyForm::selectPlayerToRemove(const int playerNum)
{
    lobby_cursor.setEnabled(true);
    playerStaging.disableCursor();

    if (playerNum != 0)
    {
        int id = lobby->getPlayerByIndex(playerNum).getId();
        controller->selectPlayerToKick(id);
    }
    else
    {
        console.setMessage("Okay, Never mind");
    }
}

void LobbyForm::startChat()
{
    chat_box.setActive(true);
    lobby_cursor.setEnabled(false);
    chat_button.setForeground(cursen::Color::GREEN);
    console.setMessage("Press Escape to Finish Chatting");
    chat_box.onEnterPress(std::bind(&LobbyForm::sendChatMessage, this));
}

void LobbyForm::stopChat()
{
    chat_box.detachEnterPress();
    chat_box.setActive(false);
    lobby_cursor.setEnabled(true);
    chat_button.setForeground(cursen::Color::WHITE);
}

void LobbyForm::sendChatMessage()
{
    controller->sendChat();
}

void LobbyForm::changeColor(int playerId, PlayerColor color)
{
    lobby->changePlayerColorById(playerId, color);
    chat_box.update(lobby->getMessages());
}

void LobbyForm::pushChatMessage(int playerId, std::string message)
{
    PlayerColor color = lobby->getPlayerColor(playerId);
    ChatEntry entry(playerId, message, color);
    lobby->pushMessage(entry);
    chat_box.update(lobby->getMessages());
}

void LobbyForm::requestAI()
{
    if (lobby->getNumPlayers() < Lobby::MAX_PLAYERS)
    {

        std::string computer_name = Player::GetComputerName();
        PlayerColor computer_color = lobby->getAvailableColorRGBY();

        Player new_ai = lobby->createPlayer(computer_name, computer_color);

        DataMessage* msg = new AddAI(new_ai);
        msg->setSendType(SendType::Both);
        DataManager::PushMessage(msg);
    }
}

void LobbyForm::kickPlayer(int id)
{
    Player p = lobby->getPlayer(id);
    lobby->removePlayer(id);
    chat_box.update(lobby->getMessages());
    console.setWarning("Later, " + p.getName());
}

void LobbyForm::close(int playerId)
{
    controller->handleClose(std::string(), false);
}

void LobbyForm::addPlayer(Player p, int sock)
{
    HostController* host_controller = (HostController*)controller;
    host_controller->putSocket(sock, p.getId());
    lobby->addPlayer(p);
    console.setMessage("Welcome, " + p.getName() + "!");

    if (lobby->isSearching() && lobby->getNumPlayers() >= Lobby::MAX_PLAYERS)
    {
        controller->handleStopSearch();
    }
}

void LobbyForm::requestClient(int sock_id, std::string name)
{
    assert(lobby->getNumPlayers() < Lobby::MAX_PLAYERS);
    PlayerColor color = lobby->getAvailableColorRGBY();

    Player new_player = lobby->createPlayer(name, color);

    Lobby client_lobby = *this->lobby;
    client_lobby.setMyId(new_player.getId());
    DataMessage* join_msg = new LobbyUpdate(client_lobby);
    join_msg->setSendType(SendType::Network);
    join_msg->setRecipient(sock_id);
    join_msg->setRecipientType(RecipientType::Single);
    DataManager::PushMessage(join_msg);

    DataMessage* add_ai_msg = new AddAI(new_player);
    add_ai_msg->setSendType(SendType::Network);
    add_ai_msg->setRecipient(sock_id);
    add_ai_msg->setRecipientType(RecipientType::Broadcast);
    DataManager::PushMessage(add_ai_msg);

    DataMessage* add_player_msg = new AddPlayer(new_player, sock_id);
    add_player_msg->setSendType(SendType::Local);
    add_player_msg->setRecipient(sock_id);
    add_player_msg->setRecipientType(RecipientType::Broadcast);
    DataManager::PushMessage(add_player_msg);
}

Lobby& LobbyForm::getLobby()
{
    return *this->lobby;
}
