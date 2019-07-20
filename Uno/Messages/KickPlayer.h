//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_KILLPLAYER_H
#define CURSEN_KILLPLAYER_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

class KickPlayer : public DataMessage {
public:

    KickPlayer() = default;

    KickPlayer(int player_id) :
            id_to_kick(player_id)
    {}

    MessageType getType() override
    {
        return MessageType::KickPlayer;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = getCurrentForm<LobbyForm>();
            lobbyForm->getController().handleKickPlayer(id_to_kick);

        CONTEXT_CHECK_END
    }

    DataMessage* clone() override
    {
        return new KickPlayer(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(KickPlayer);
    }

    size_t serialize(char* const buffer) const override
    {
        size_t written = DataMessage::serialize(buffer);

        written += Serializable::Serialize(buffer + written, id_to_kick);

        return written;
    }

    size_t deserialize(const char* const buffer) override
    {
        size_t read = DataMessage::deserialize(buffer);

        read += Serializable::Deserialize(buffer + read, id_to_kick);

        return read;
    }

private:

    int id_to_kick;

};

#endif //CURSEN_KILLPLAYER_H
