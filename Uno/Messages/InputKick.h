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
        player_to_kick(player_id)
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
            if (player_to_kick > 0 && player_to_kick < lobbyForm->getLobby().getNumPlayers())
            {
                DataMessage* msg = new KickPlayer(player_to_kick);
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);

            }
        }
    }

    DataMessage* copy() override
    {
        return new InputKick(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputKick);
    }

private:

    int player_to_kick;

};

#endif //CURSEN_INPUTKICK_H
