//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTCLOSE_H
#define CURSEN_INPUTCLOSE_H

#include "DataMessage.h"
#include "CloseRoom.h"
#include "KickPlayer.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

class InputCloseRoom : public DataMessage
{

public:

    InputCloseRoom() = default;
    InputCloseRoom(int id) :
        id(id)
    {}

    MessageType getType() override
    {
        return MessageType::InputClose;
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
            if (id == lobbyForm->getLobby().getMyId())
            {
                // Security - the host should reject messages without the host's id
                lobbyForm->getController().sendCloseMessages();
            }
        }
    }

    DataMessage* clone() override
    {
        return new InputCloseRoom(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputCloseRoom);
    };

private:

    int id;

};

#endif //CURSEN_INPUTCLOSE_H
