//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTADDAI_H
#define CURSEN_INPUTADDAI_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "AddPlayer.h"

class InputAddAi : public DataMessage {
public:

    MessageType getType() override
    {
        return MessageType::InputAddAi;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            Lobby& lobby = lobbyForm->getLobby();

            if (lobby.getNumPlayers() < Lobby::MAX_PLAYERS)
            {
                std::string computer_name = Player::GetComputerName();
                PlayerColor computer_color = lobby.getAvailableColorRGBY();

                Player new_ai = lobby.createAI(computer_name, computer_color);

                DataMessage* msg = new AddPlayer(new_ai);
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputAddAi(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputAddAi);
    }

};

#endif //CURSEN_INPUTADDAI_H
