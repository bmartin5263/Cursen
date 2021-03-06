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
    PushChatLog(int player_index, std::string msg) :
            message(msg), player_index(player_index)
    {}

    MessageType getType() override
    {
        return MessageType::PushChatLog;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->pushChatMessage(player_index, message);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new PushChatLog(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(PushChatLog);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t bytes_written = DataMessage::serialize(buffer);

        bytes_written += Serialize(buffer + bytes_written, player_index);
        bytes_written += Serialize(buffer + bytes_written, message);

        return bytes_written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t bytes_read = DataMessage::deserialize(buffer);

        bytes_read += Deserialize(buffer + bytes_read, player_index);
        bytes_read += Deserialize(buffer + bytes_read, message);

        return bytes_read;
    }

private:

    std::string message;
    int player_index;

};

#endif //CURSEN_ADDCHATMESSAGE_H
