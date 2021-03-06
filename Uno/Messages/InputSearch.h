//
// Created by Brandon Martin on 6/12/19.
//

#ifndef CURSEN_INPUTSEARCH_H
#define CURSEN_INPUTSEARCH_H

#include "Uno/Data/DataManager.h"
#include "Uno/Forms/LobbyForm.h"
#include "Cursen/CursenApplication.h"
#include "Uno/Lobby/LobbyController.h"
#include "StopSearch.h"
#include "StartSearch.h"

class InputSearch : public DataMessage {

public:

    MessageType getType() override
    {
        return MessageType::InputSearch;
    }

    Context getContext() override
    {
        return Context::ContextLobby;
    }

    void execute() override
    {
        CONTEXT_CHECK_BEGIN

            LobbyForm* lobbyForm = GetCurrentForm<LobbyForm>();
            if (lobbyForm->getLobby().isSearching())
            {
                DataMessage* msg = new StopSearch;
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }
            else
            {
                DataMessage* msg = new StartSearch;
                msg->setSendType(SendType::Both);
                DataManager::PushMessage(msg);
            }

        CONTEXT_END
    }

    DataMessage* clone() override
    {
        return new InputSearch(*this);
    }

    size_t sizeOf() const override
    {
        return sizeof(InputSearch);
    }

};

#endif //CURSEN_INPUTSEARCH_H
