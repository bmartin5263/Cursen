//
// Created by Brandon Martin on 5/20/19.
//

#include "ClientController.h"
#include "Uno/Messages/InputChangeColor.h"
#include "Uno/Constants.h"
#include "Uno/Messages/InputChat.h"

ClientController::ClientController(LobbyForm* form) : LobbyController(form)
{

}

void ClientController::initialize()
{
    lobbyForm->initializeForClient();
}

void ClientController::destroy()
{
    lobbyForm->leaveClient();
}

void ClientController::clickStart()
{
    throw std::logic_error("Client cannot start game.");
}

void ClientController::clickAddAI()
{
    throw std::logic_error("Client cannot add AI.");
}

void ClientController::clickSearch()
{
    throw std::logic_error("Client cannot search.");
}

void ClientController::clickKick()
{
    throw std::logic_error("Client cannot kick.");
}

void ClientController::clickClose()
{
    destroy();
}

void ClientController::clickChangeColor()
{
    DataMessage* msg = new InputChangeColor(0);
    msg->setSendType(SendType::Network);
    DataManager::PushMessage(msg);
}

void ClientController::sendChat()
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
        msg->setSendType(SendType::Network);
        DataManager::PushMessage(msg);

        chatBox.clearMessage();
    }
    else
    {
        lobbyForm->stopChat();
    }
}

void ClientController::kickPlayer(int id)
{
    throw std::logic_error("Client cannot kick players.");
}
