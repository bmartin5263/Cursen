//
// Created by Brandon Martin on 5/20/19.
//

#include "HostController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Constants.h"
#include "Uno/Messages/InputChat.h"
#include "Uno/Messages/InputAddAi.h"
#include "Uno/Messages/InputKick.h"

HostController::HostController(LobbyForm* lobbyForm) : LobbyController(lobbyForm)
{}


void HostController::initialize()
{
    lobbyForm->initializeForHost();
}

void HostController::destroy()
{
    lobbyForm->leaveHost();
}

void HostController::clickStart()
{
    // Broadcast message to start the game
    lobbyForm->getConsole().setText("Start Clicked!");
}

void HostController::clickAddAI()
{
    DataMessage* msg = new InputAddAi;
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::clickSearch()
{
    // Broadcast message to twirl
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Search Clicked!");
    lobbyForm->toggleSearch();
}

void HostController::clickKick()
{
    // First select player
    // then broadcast message
    UnoConsole& console = lobbyForm->getConsole();
    console.setText("Kick Clicked!");
    lobbyForm->enableRemovePlayerCursor();
}

void HostController::clickClose()
{
    // Broadcast close
    destroy();
}

void HostController::clickChangeColor()
{
    // Broadcast color change
    DataMessage* msg = new InputChangeColor(0);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

void HostController::sendChat()
{
    ChatBox& chatBox = lobbyForm->getChatBox();

    std::string text = Constants::rtrim(chatBox.getMessage());
    if (!text.empty())
    {
        size_t text_len = text.length();
        char* raw_text = new char[text_len + 1];

        const char* str = text.c_str();

        memcpy(raw_text, str, text_len + 1);

        raw_text[text_len] = '\0';

        DataMessage* msg = new InputChat(0, text_len, raw_text);
        msg->setSendType(SendType::Local);
        DataManager::PushMessage(msg);

        chatBox.clearMessage();
    }
    else
    {
        lobbyForm->stopChat();
    }
}

void HostController::kickPlayer(int id)
{
    DataMessage* msg = new InputKick(id);
    msg->setSendType(SendType::Local);
    DataManager::PushMessage(msg);
}

