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

    InputChat(std::string msg) :
        message(msg)
    {}

    MessageType getType() override
    {
        return MessageType::InputChat;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->getController().handleChatInput(getSender(), message);

        CONTEXT_END
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

        bytes_written += Serialize(buffer + bytes_written, message);

        return bytes_written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t bytes_read = DataMessage::deserialize(buffer);

        bytes_read += Deserialize(buffer + bytes_read, message);

        return bytes_read;
    }

private:

    std::string message;

};

#endif //CURSEN_INPUTCHAT_H
