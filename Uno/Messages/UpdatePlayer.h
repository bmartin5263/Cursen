//
// Created by Brandon Martin on 9/4/19.
//

#ifndef CURSEN_UPDATEPLAYER_H
#define CURSEN_UPDATEPLAYER_H


#include <Uno/Data/DataManager.h>
#include "DataMessage.h"

class UpdatePlayer : public DataMessage {
public:

    UpdatePlayer() = default;

    UpdatePlayer(const Player& p, int index):
            new_player(p), index(index)
    {}

    MessageType getType() override
    {
        return MessageType::UpdatePlayer;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

        LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
        lobbyForm->getController().handleUpdatePlayer(new_player, index);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new UpdatePlayer(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(UpdatePlayer);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += new_player.serialize(buffer + written);
        written += Serializable::Serialize(buffer + written, index);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += new_player.deserialize(buffer + read);
        read += Serializable::Deserialize(buffer + read, index);

        return read;
    }

private:

    Player new_player;
    int index;

};


#endif //CURSEN_UPDATEPLAYER_H
