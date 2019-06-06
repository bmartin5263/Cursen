//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_ADDCHATMESSAGE_H
#define CURSEN_ADDCHATMESSAGE_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Data/DataManager.h"

class PushChatLog : public DataMessage {

public:

    PushChatLog() = default;
    PushChatLog(int id, size_t len, char* message) :
        id(id), len(len), message(message)
    {}

    MessageType getType() override
    {
        return MessageType::PushChatLog;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            std::string msg(message);
            lobbyForm->pushChatMessage(id, msg);
        }
    }

    DataMessage* copy() override
    {
        return new PushChatLog(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(PushChatLog);
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
        bytes_read += Deserialize(buffer, message, len);
        return bytes_read;
    }

private:

    char* message;
    size_t len;
    int id;

};

#endif //CURSEN_ADDCHATMESSAGE_H
