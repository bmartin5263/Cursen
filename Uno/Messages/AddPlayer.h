//
// Created by Brandon Martin on 6/11/19.
//

#ifndef CURSEN_ADDPLAYER_H
#define CURSEN_ADDPLAYER_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Uno/Data/DataManager.h"
#include "Cursen/CursenApplication.h"

class AddPlayer : public DataMessage {
public:

    AddPlayer() = default;

    AddPlayer(const Player& p, const int sock):
            new_player(p), sock(sock)
    {}

    MessageType getType() override
    {
        return MessageType::AddPlayer;
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
            lobbyForm->addPlayer(new_player, sock);
        }
    }

    DataMessage* clone() override
    {
        return new AddPlayer(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(AddPlayer);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += new_player.serialize(buffer + written);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += new_player.deserialize(buffer + read);

        return read;
    }

private:

    Player new_player;
    int sock;

};

#endif //CURSEN_ADDPLAYER_H
