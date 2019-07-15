//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_STOPSEARCH_H
#define CURSEN_STOPSEARCH_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Lobby/LobbyController.h"

class StopSearch : public DataMessage {

public:

    MessageType getType() override
    {
        return MessageType::StopSearch;
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
            lobbyForm->getController().handleStopSearch();
        }
    }

    DataMessage* clone() override
    {
        return new StopSearch(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(StopSearch);
    }

};

#endif //CURSEN_STOPSEARCH_H
