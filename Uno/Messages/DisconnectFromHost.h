//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_DISCONNECTFROMHOST_H
#define CURSEN_DISCONNECTFROMHOST_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"

class DisconnectFromHost : public DataMessage
{
public:

    DisconnectFromHost() = default;

    DisconnectFromHost(std::string msg, bool kick) :
        message(msg), kicked(kick)
    {

    }

    MessageType getType() override
    {
        return MessageType::DisconnectFromHost;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->getController().handleClose(message, kicked);

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return nullptr;
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, message);
        written += Serializable::Serialize(buffer + written, kicked);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, message);
        read += Serializable::Deserialize(buffer + read, kicked);

        return read;
    }

private:

    std::string message;
    bool kicked;

};

#endif //CURSEN_DISCONNECTFROMHOST_H
