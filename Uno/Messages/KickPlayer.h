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
            player_to_kick(player_id)
    {}

    MessageType getType() override
    {
        return MessageType::KickPlayer;
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
            lobbyForm->kickPlayer(player_to_kick);
        }
    }

    DataMessage* copy() override
    {
        return nullptr;
    }

    size_t sizeOf() const override
    {
        return 0;
    }

private:

    int player_to_kick;

};

#endif //CURSEN_KILLPLAYER_H
