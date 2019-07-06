//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTKICK_H
#define CURSEN_INPUTKICK_H

#include "DataMessage.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Data/DataManager.h"
#include "KickPlayer.h"


class InputKick : public DataMessage {
public:

    InputKick() = default;

    InputKick(int player_id) :
            id_to_kick(player_id)
    {}

    MessageType getType() override
    {
        return MessageType::InputKick;
    }

    Context getContext() override
    {
        return Context::Lobby;
    }

    void execute() override
    {
        if (DataManager::GetContext() == getContext())
        {
            LobbyForm* lobbyForm = (LobbyForm*)cursen::CursenApplication::GetCurrentForm();
            if (lobbyForm->getLobby().hasId(id_to_kick))
            {
                lobbyForm->getController().sendKickMessages(id_to_kick);
            }
        }
    }

    DataMessage* clone() override
    {
        return new InputKick(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputKick);
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

#endif //CURSEN_INPUTKICK_H