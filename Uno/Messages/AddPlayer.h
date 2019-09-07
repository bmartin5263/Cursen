//
// Created by Brandon Martin on 9/4/19.
//

#ifndef CURSEN_NEWADDPLAYER_H
#define CURSEN_NEWADDPLAYER_H


#include <Uno/Data/DataManager.h>
#include "DataMessage.h"

class AddPlayer : public DataMessage {
public:

    AddPlayer() = default;

    AddPlayer(const Player& p):
            new_player(p)
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
        CONTEXT_CHECK_BEGIN

        LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
        lobbyForm->getController().handleAddPlayer(new_player);

        CONTEXT_END
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

};


#endif //CURSEN_NEWADDPLAYER_H
