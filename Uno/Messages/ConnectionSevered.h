//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_CLIENTHASDISCONNECTED_H
#define CURSEN_CLIENTHASDISCONNECTED_H

#include "Uno/Data/DataManager.h"

class ConnectionSevered : public DataMessage {

public:

    ConnectionSevered() = default;

    ConnectionSevered(int sock) :
        sock(sock)
    {
    }

    MessageType getType() override
    {
        return MessageType::ConnectionSevered;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            auto* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            lobbyForm->getController().handleDisconnect(getSender());
        }
    }

    DataMessage* clone() override
    {
        return new ConnectionSevered(*this);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, sock);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, sock);

        return read;
    }

private:

    int sock;

};

#endif //CURSEN_CLIENTHASDISCONNECTED_H
