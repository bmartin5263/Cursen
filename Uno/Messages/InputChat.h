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

    InputChat(int id, std::string msg) :
        id(id), message(msg)
    {}

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
            DataMessage* msg = new PushChatLog(id, message);
            msg->setSendType(SendType::Both);
            DataManager::PushMessage(msg);
        }
    }

    DataMessage* clone() override
    {
        return new InputChat(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputChat);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t bytes_written = DataMessage::serialize(buffer);

        bytes_written += Serialize(buffer + bytes_written, id);
        bytes_written += Serialize(buffer + bytes_written, message);

        return bytes_written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t bytes_read = DataMessage::deserialize(buffer);

        bytes_read += Deserialize(buffer + bytes_read, id);
        bytes_read += Deserialize(buffer + bytes_read, message);

        return bytes_read;
    }

private:

    std::string message;
    int id;

};

#endif //CURSEN_INPUTCHAT_H
