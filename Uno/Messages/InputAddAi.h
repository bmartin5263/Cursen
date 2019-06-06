//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_INPUTADDAI_H
#define CURSEN_INPUTADDAI_H

#include "DataMessage.h"
#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"

class InputAddAi : public DataMessage {
public:

    MessageType getType() override
    {
        return MessageType::InputAddAi;
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
            lobbyForm->requestAI();
        }
    }

    DataMessage* copy() override
    {
        return new InputAddAi(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputAddAi);
    }


};

#endif //CURSEN_INPUTADDAI_H
