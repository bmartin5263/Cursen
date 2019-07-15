//
// Created by Brandon Martin on 6/11/19.
//

#ifndef CURSEN_LOBBYUPDATE_H
#define CURSEN_LOBBYUPDATE_H

#include "DataMessage.h"
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
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            lobbyForm->updateLobby(lobby);
        }
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
