//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTCHAT_H
#define CURSEN_INPUTCHAT_H

#include "DataMessage.h"
#include "Uno/Other/ChatEntry.h"
#include "Uno/Data/DataManager.h"
#include "PushChatLog.h"

class InputChat : public DataMessage {

public:

    InputChat() = default;

    InputChat(int id, size_t len, char* message) :
        id(id), len(len), message(message)
    {}

    ~InputChat() {
        delete message;
    }

    MessageType getType() override
    {
        return MessageType::InputChat;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {

            char* text = new char[len + 1];
            memcpy(text, message, len + 1);

            DataMessage* msg = new PushChatLog(id, len, text);
            msg->setSendType(SendType::Both);
            DataManager::PushMessage(msg);
        }
    }

    DataMessage* copy() override
    {
        return new InputChat(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputChat);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t bytes_written = 0;
        bytes_written += Serialize(buffer + bytes_written, id);
        bytes_written += Serialize(buffer + bytes_written, len);
        bytes_written += Serialize(buffer + bytes_written, message, len);
        return bytes_written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t bytes_read = 0;
        bytes_read += Deserialize(buffer, id);
        bytes_read += Deserialize(buffer, len);
        message = new char[len + 1];
        bytes_read += Deserialize(buffer, message, len);
        message[len] = '\0';
        return bytes_read;
    }

private:

    char* message;
    size_t len;
    int id;

};

#endif //CURSEN_INPUTCHAT_H
