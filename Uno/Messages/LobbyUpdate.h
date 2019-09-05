//
// Created by Brandon Martin on 6/11/19.
//

#ifndef CURSEN_LOBBYUPDATE_H
#define CURSEN_LOBBYUPDATE_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/GameObjects/Lobby.h"

class LobbyUpdate : public DataMessage
{
public:

    LobbyUpdate() = default;

    LobbyUpdate(Lobby lobby) :
        lobby(lobby)
    {}

    MessageType getType() override
    {
        return MessageType::LobbyUpdate;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            lobbyForm->updateLobby(lobby);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new LobbyUpdate(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(LobbyUpdate);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += lobby.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += lobby.deserialize(buffer + read);

        return read;
    }

private:

    Lobby lobby;

};

#endif //CURSEN_LOBBYUPDATE_H
